#include "DropPoolLCLazarus.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolLCLazarus::PoolName = "lc-lazarus";

DropPoolLCLazarus* DropPoolLCLazarus::create(ValueMap& properties)
{
	DropPoolLCLazarus* instance = new DropPoolLCLazarus(properties);

	instance->autorelease();

	return instance;
}

DropPoolLCLazarus::DropPoolLCLazarus(ValueMap& properties) : super(properties, DropPoolLCLazarus::PoolName, SampleMethod::Random, 1, 2, CurrencyPoolLCGeneric::create(properties),
	{
		CardPoolTier5::create(SampleMethod::Random, 0, 1),
		AlchemyPoolTier5::create(SampleMethod::Random, 1, 2),
		SmithingPoolTier5::create(SampleMethod::Random, 1, 2),
	})
{
	this->addItemToPool(ItemChance::create(AncientKey::create(), ItemChance::Probability::Guaranteed));
}

DropPoolLCLazarus::~DropPoolLCLazarus()
{
}
