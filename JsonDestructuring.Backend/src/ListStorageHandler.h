#pragma once

#include <memory>
#include "CBase.h"

namespace JsonDestructure
{
    class CBase;
    class Storage;


    /*
    * This class decouples the ISystemList from Storage classes
    * ISystemList & Storage are template classese -- which means the classes are header only
    * Including 'Storage.h' in 'ISystemList.h' would tightly couple them to the JSON lib
    * All list functions on Storage are handled here
    */
    class ListStorageHandler : public CBase
    {
    public:
        ListStorageHandler(std::shared_ptr<Storage> listStorage);
        
        int Count();

        std::shared_ptr<Storage> Get(unsigned int index);

        // NOTE Needs a CBase (currently) -- to make our lives easier
        void Add(CBase* newItem);
    };
}