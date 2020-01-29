#include "ErrorDropPool.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ErrorDropPool::PoolName = "drop-error";

ErrorDropPool* ErrorDropPool::create(ValueMap& properties)
{
	ErrorDropPool* instance = new ErrorDropPool(properties);

	instance->autorelease();

	return instance;
}

ErrorDropPool::ErrorDropPool(ValueMap& properties) : super(properties, ErrorDropPool::PoolName, SampleMethod::Guarantee, 1, 1, nullptr, { })
{
	this->addItemToPool(ItemChance::create(MissingNo::create(), ItemChance::Probability::Guaranteed));
}

ErrorDropPool::~ErrorDropPool()
{
}
