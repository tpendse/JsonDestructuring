#pragma once


#include <memory>
#include <vector>
#include <json.hpp>

#include "CBaseList.h"

namespace JsonDestructure
{
    //---------------------------------------------------------------------------------------------------------------------------
    /* 
    * Helper macros -- to be used in model sources
    */
#define RETURN_OBJECT(ObjectType, PropertyName) return _storage->Get<ObjectType>(PropertyName);

#define RETURN_BASIC(BasicType, PropertyName) return (BasicType)*(_storage->Get<BasicType>(PropertyName).get());

#define RETURN_LIST(ObjectType, PropertyName) return _storage->GetList<ObjectType>(PropertyName);

#define SET_VALUE(PropertyName, PropertyValue) _storage->Set(PropertyName, PropertyValue);

    //---------------------------------------------------------------------------------------------------------------------------

	class Storage; // Fwd-decl to allow nesting

	class Storage
	{
        friend class ListStorageHandler;

	private:
        bool                                        _isRoot;
        bool                                        _createEmptyElements;
		std::shared_ptr<nlohmann::json>             _document;
		std::shared_ptr<nlohmann::json::iterator>   _itr;

        /*
        * Returns reference to the JSON object based on the type of storage.
        * For constructed JSON storage, there is no need for an iterator
        * since this model is not part of a larger document. The document
        * holds all the data
        */
        nlohmann::json& getJson()
        {
            return _itr == nullptr ? (*_document.get()) : _itr->value();
        }


        void AssertType(const nlohmann::json& json, const std::vector<nlohmann::detail::value_t>& expectedTypes) const
        {
            // null types are unsupported and need to be handled by 'Valid' checks
            if (json.is_null()) return;

            const auto actual_type = json.type();
            for (auto expectedType : expectedTypes)
                if (expectedType == actual_type)
                    return;

            throw new std::runtime_error("JSON type is not as expected!");
        }

	public:

		Storage(
            std::shared_ptr<nlohmann::json> document, 
            std::shared_ptr<nlohmann::json::iterator> iterator, 
            bool isRoot = false)
			: _document(document), _itr(iterator), _isRoot(isRoot), _createEmptyElements(false)
		{
            if (_document == nullptr && _itr == nullptr)
                throw new std::runtime_error("Document or Iterator invalid!");
		}

        bool IsRoot() const
        {
            return _isRoot || _itr == nullptr;
        }

        void SetCreateEmptyElements(bool flag)
        {
            _createEmptyElements = flag;
        }

        std::string ToString(bool indent = false)
        {
            const int indent_level = indent ? 3 : -1;
            return this->getJson().dump();
        }

        std::string Document(bool indent = false)
        {
            const int indent_level = indent ? 3 : -1;
            return _document->dump(indent_level);
        }


        /*
        * Meant to be a replacement for nullptr checks
        * i.e. `model != nullptr` to be replaced by `model.Valid()`
        */
        bool Valid() const
        {
            try
            {
                if (_document == nullptr) return false;
                return _itr == nullptr
                    ? !_document->is_null()    && !_document->empty()
                    : !_itr->value().is_null() && !_itr->value().empty();
            }
            catch (...)
            { 
                return false; 
            }
        }


        bool TryGet(const std::string& keyName, nlohmann::json::iterator& outFound)
        {
            nlohmann::json& json = this->getJson();
            if (!json.contains(keyName))
                return false;

            outFound = json.find(keyName);
            return true;
        }


        //-----------------------------------------------------------------------------------------------------------------------
        // GETTERS
        //-----------------------------------------------------------------------------------------------------------------------


		template<typename T>
		std::shared_ptr<T> Get(const std::string& name)
		{
            nlohmann::json::iterator foundItr;
            const bool found = this->TryGet(name, foundItr);

            if (!found)
            {
                if (!_createEmptyElements)
                    throw new std::runtime_error("Cannot find specified key!");
                try
                {
                    this->getJson()[name] = nlohmann::json::object();
                    this->TryGet(name, foundItr);
                }
                catch (...)
                {
                    return nullptr;
                }
               
            }

            AssertType(foundItr.value(), { nlohmann::detail::value_t::object });

			std::shared_ptr<nlohmann::json::iterator> heap_child(new nlohmann::json::iterator(foundItr));
			std::shared_ptr<Storage> storage(new Storage(_document, heap_child));
            storage->SetCreateEmptyElements(_createEmptyElements);

			return std::shared_ptr<T>(new T(storage));
		}


        template<typename T>
        std::shared_ptr<ISystemList<T>> GetList(const std::string& name)
        {
            nlohmann::json::iterator foundItr;
            const bool found = this->TryGet(name, foundItr);

            if(!found)
            {
                if(!_createEmptyElements)
                    throw new std::runtime_error("Cannot find specified key!");

                this->getJson()[name] = nlohmann::json::array();
                this->TryGet(name, foundItr);
            }

            AssertType(foundItr.value(), { nlohmann::detail::value_t::array });

            std::shared_ptr<nlohmann::json::iterator> heap_child(new nlohmann::json::iterator(foundItr));
            std::shared_ptr<Storage> storage(new Storage(_document, heap_child));

            return std::shared_ptr<CBaseList<T>>(new CBaseList<T>(storage));
        }

        template<typename T>
        std::vector<T> GetBasicList(const std::string& name)
        {
            std::vector<T> outList;

            nlohmann::json::iterator foundItr;
            if (!this->TryGet(name, foundItr))
                throw new std::runtime_error("Cannot find specified key!");

            AssertType(foundItr.value(), { nlohmann::detail::value_t::array });

            auto items = foundItr->items();
            for (auto items_itr = items.begin(); items_itr != items.end(); ++items_itr)
            {
                outList.push_back(items_itr.value());
            }

            return outList;

        }


        //-----------------------------------------------------------------------------------------------------------------------
        // SETTERS
        //-----------------------------------------------------------------------------------------------------------------------


        template <typename T>
        void Set(const std::string& name, std::shared_ptr<T> value)
        {
            auto json = nlohmann::json::parse(value->toString());
            this->getJson()[name] = json;
        }


        void Set(const std::string& name, const std::string& value)
        {
            this->getJson()[name] = value;
        }


        void Set(const std::string& name, int value)
        {
            this->getJson()[name] = value;
        }


        void Set(const std::string& name, bool value)
        {
            this->getJson()[name] = value;
        }
	};

    //---------------------------------------------------------------------------------------------------------------------------
}


template<>
std::shared_ptr<std::string> JsonDestructure::Storage::Get(const std::string& name);


template<>
std::shared_ptr<int> JsonDestructure::Storage::Get(const std::string& name);


template<>
std::shared_ptr<bool> JsonDestructure::Storage::Get(const std::string& name);