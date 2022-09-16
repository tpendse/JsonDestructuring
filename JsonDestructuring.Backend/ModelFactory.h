#pragma once

#include <string>
#include <memory>
#include "ISystemList.h"
#include "Enums.h"

namespace JsonDestructure
{
    class Storage;

    class ModelFactory
    {
    private:
        static std::shared_ptr<Storage> CreateEmptyStorage();
        static std::shared_ptr<Storage> CreateStorageFromString(const std::string& content);
        static std::shared_ptr<Storage> CreateStorageFromHttpResponse(const std::string& content);

    public:
        template<typename T>
        static std::shared_ptr<T> New()
        {
            auto storage = CreateEmptyStorage();
            return std::shared_ptr<T>(new T(storage));
        }

        template<typename T>
        static std::shared_ptr<T> FromJson(const std::string& content)
        {
            auto storage = CreateStorageFromString(content);
            return std::shared_ptr<T>(new T(storage));
        }

        template<typename T>
        static std::shared_ptr<T> FromHttp(const std::string& content, CHttpStatusCode responseCode)
        {
            auto storage = content.empty() ? CreateEmptyStorage() : CreateStorageFromHttpResponse(content);
            return std::shared_ptr<T>(new T(storage, responseCode));
        }
    };
}