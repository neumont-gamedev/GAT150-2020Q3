#pragma once
#include "pch.h"

class Resource
{
public:
	Resource() {}
	virtual ~Resource() {}

	virtual bool Create(const std::string& name) = 0;
	virtual void Destroy() = 0;
};
