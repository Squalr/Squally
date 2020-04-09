#include "EmptyDropPool.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EmptyDropPool::PoolName = "empty";

EmptyDropPool* EmptyDropPool::create(ValueMap& properties)
{
	EmptyDropPool* instance = new EmptyDropPool(properties);

	instance->autorelease();

	return instance;
}

EmptyDropPool::EmptyDropPool(ValueMap& properties) : super(ValueMap(), EmptyDropPool::PoolName, SampleMethod::Guarantee, 0, 0, nullptr, { })
{
}

EmptyDropPool::~EmptyDropPool()
{
}
