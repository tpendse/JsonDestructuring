#pragma once

#include "dllmain.h"
#include <memory>
#include "CBase.h"
#include "ISystemList.h"
#include "ListStorageHandler.h"

#include <exception>

namespace JsonDestructure
{
    class Storage;

#pragma warning(push)
#pragma warning(disable:4251)

    template<typename T>
    class DLL CBaseList : public ISystemList<T>
    {
    private:
        /*
        * ListStorageHandler decouples the ISystemList from Storage classes
        * ISystemList & Storage are template classese -- which means the classes are header only
        * Including 'Storage.h' in 'ISystemList.h' would tightly couple them to the JSON lib
        */
        std::unique_ptr<ListStorageHandler> _listStorageHandler;

    public:
        CBaseList(std::shared_ptr<Storage> storage)
        {
            _listStorageHandler.reset(new ListStorageHandler(storage));
        }

        virtual void Add(T* item) override
        {
            auto cbase = dynamic_cast<CBase*>(item);
            if (cbase == nullptr)
                throw new std::runtime_error("Incorrect type! Added item needs to derive from CBase.");

            _listStorageHandler->Add(cbase);
        }

        virtual int Count()
        {
            return _listStorageHandler->Count();
        }

        virtual std::shared_ptr<T> operator[](unsigned int index) const
        {
            auto storage = _listStorageHandler->Get(index);
            return std::shared_ptr<T>(new T(storage));
        }

        virtual bool Valid()
        {
            return _listStorageHandler->Valid();
        }
    };

#pragma warning(pop)
}