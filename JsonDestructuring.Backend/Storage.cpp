#pragma once

#include "pch.h"
#include "Storage.h"

using namespace JsonDestructure;

template<>
std::shared_ptr<std::string> Storage::Get(const std::string& name)
{
    nlohmann::json::iterator foundItr;
    if (!this->TryGet(name, foundItr))
        throw std::runtime_error("Cannot find specified key!");

    AssertType(foundItr.value(), { nlohmann::detail::value_t::string });
    return std::shared_ptr<std::string>(new std::string(foundItr.value()));
}


template<>
std::shared_ptr<int> Storage::Get(const std::string& name)
{
    nlohmann::json::iterator foundItr;
    if (!this->TryGet(name, foundItr))
        throw std::runtime_error("Cannot find specified key!");

    AssertType(
        foundItr.value(),
        {
            nlohmann::detail::value_t::number_integer,
            nlohmann::detail::value_t::number_unsigned,
            nlohmann::detail::value_t::binary /* TODO Check if this ok */
        }
    );
    return std::shared_ptr<int>(new int(foundItr.value()));
}


template<>
std::shared_ptr<bool> Storage::Get(const std::string& name)
{
    nlohmann::json::iterator foundItr;
    if (!this->TryGet(name, foundItr))
        throw std::runtime_error("Cannot find specified key!");

    AssertType(foundItr.value(), { nlohmann::detail::value_t::boolean });
    return std::shared_ptr<bool>(new bool(foundItr.value()));
}
