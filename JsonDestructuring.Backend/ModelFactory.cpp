#pragma once

#include "pch.h"
#include <json.hpp>
#include "ModelFactory.h"
#include "Storage.h"


using namespace JsonDestructure;
using namespace nlohmann;

bool isMostLikelyJson(const std::string& input)
{
    return 
        input.find("{") != std::string::npos && 
        input.find("}") != std::string::npos && 
        input.find(":") != std::string::npos;
}

std::shared_ptr<Storage> ModelFactory::CreateEmptyStorage()
{
    std::shared_ptr<json> document(new json(json::parse("{}")));
    std::shared_ptr<json::iterator> itr(nullptr);

    auto storage = std::shared_ptr<Storage>(new Storage(document, itr, true));
    storage->SetCreateEmptyElements(true);
    return storage;
}

std::shared_ptr<Storage> ModelFactory::CreateStorageFromString(const std::string& content)
{
    std::shared_ptr<json> document(new json(json::parse(content)));
    std::shared_ptr<json::iterator> itr(new json::iterator(document->begin()));

    auto storage = std::shared_ptr<Storage>(new Storage(document, itr, true));
    storage->SetCreateEmptyElements(false);
    return storage;
}

std::shared_ptr<Storage> ModelFactory::CreateStorageFromHttpResponse(const std::string& content)
{
    std::stringstream ss;

    ss << "{ \"response\": ";
    if (!isMostLikelyJson(content))
    {
        ss << "{ \"content\" : \"" << content << "\" }";
    }
    else
    {
        ss << content;
    }
    ss << "}";
    const std::string response_body = ss.str();

    return CreateStorageFromString(response_body);
}
