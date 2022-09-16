#pragma once

#include "pch.h"
#include <json.hpp>

#include "ListStorageHandler.h"
#include "Storage.h"

using namespace JsonDestructure;
using namespace nlohmann;

ListStorageHandler::ListStorageHandler(std::shared_ptr<Storage> listStorage) : CBase(listStorage)
{
}

int ListStorageHandler::Count()
{
    return (int)_storage->getJson().size();
}

std::shared_ptr<Storage> ListStorageHandler::Get(unsigned int index)
{
    const auto size = _storage->getJson().size();
    auto list_itr = _storage->getJson().items().begin();

    if(index >= size)
        throw new std::runtime_error("List index exceeds bounds!");

    std::advance(list_itr, index);

    /*
    * - The `get_anchor()` method was added by MSC Licensing team to nlohmann json.
    *   `items()` returns an `iterator_proxy`, which wraps `iterator`, the object we need.
    * - Instead of changing/wrapping our storage type to work with iterator_proxy, we
    *   modified the header only json lib instead
    */
    std::shared_ptr<nlohmann::json::iterator> heap_child(new nlohmann::json::iterator(list_itr.get_anchor()));

    return std::shared_ptr<Storage>(new Storage(_storage->_document, heap_child));
}

void ListStorageHandler::Add(CBase* newItem)
{
    const auto newItemJson = nlohmann::json::parse(newItem->toString());
    _storage->getJson().push_back(newItemJson);

    auto newStorage = this->Get(this->Count() - 1);

    newItem->Replace(newStorage);
}
