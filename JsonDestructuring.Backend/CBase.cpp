#pragma once

#include "pch.h"
#include <exception>
#include "CBase.h"
#include "Storage.h"


using namespace JsonDestructure;

CBase::CBase(std::shared_ptr<Storage> storage) 
    : _storage(storage)
#ifdef _DEBUG
    , _str("")
#endif
{
#ifdef _DEBUG
    _str = _storage->ToString(true);
#endif // _DEBUG
}

CBase::~CBase()
{
}

bool CBase::IsRoot() const
{
    return _storage->IsRoot();
}

void CBase::Replace(std::shared_ptr<Storage> newStorage)
{
    _storage = newStorage;
}

std::string CBase::toString()
{
    auto str = _storage->ToString();
#ifdef _DEBUG
    _str = str;
    return _str;
#else
    return str;
#endif
}

std::string CBase::Document()
{
    return _storage->Document();
}

bool CBase::Valid()
{
    return _storage->Valid();
}

void CBase::SetCreateEmptyElements(bool flag)
{
    _storage->SetCreateEmptyElements(flag);
}
