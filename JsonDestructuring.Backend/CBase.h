#pragma once

// NOTE Do not remove these includes -- used in all CBase derived classes/models
#include "dllmain.h"
#include <memory>
#include <string>
#include "Enums.h"
#include <json.hpp>


using namespace nlohmann;

namespace JsonDestructure
{
    class Storage;

#pragma warning(push)
#pragma warning(disable:4251)

    /*
    * Base wrapper class for all wrapper classes
    */
	class DLL CBase
	{
#ifdef _DEBUG
    protected:
        std::string _str;
#endif
	protected:
        std::shared_ptr<Storage> _storage;

	public:
		CBase(std::shared_ptr<Storage> storage);

        virtual void Replace(std::shared_ptr<Storage> newStorage);

		virtual ~CBase();

        virtual bool IsRoot() const;

        virtual std::string toString();

        virtual std::string Document();

		virtual bool Valid();

        void SetCreateEmptyElements(bool flag);
	};


    //==========================================================================================

    class CResponseBase : public CBase
    {
    private:
        const CHttpStatusCode _statusCode;

    public:
        CResponseBase(
            std::shared_ptr<Storage> storage,
            CHttpStatusCode statusCode)
            : CBase(storage), _statusCode(statusCode)
        {
        }
        
        virtual CHttpStatusCode StatusCode() const { return _statusCode; }

        virtual std::string ResponseContent() { return toString(); }
        virtual std::string ResponseDescription() 
        {
            std::string jsonString = toString();
            std::string description = jsonString; // default if parsing fails

            // json search for the description field.
            auto json_doc = json::parse(jsonString);
            if (!json_doc.is_null())
            {
                std::string jkey = "errorResponse";
                auto result = json_doc.find(jkey);
                if (result != json_doc.end())
                {
                    std::string dkey = "description";
                    description = result->value(dkey, jsonString);
                }
            }

            return description;
        }
    };

#pragma warning(pop)
}