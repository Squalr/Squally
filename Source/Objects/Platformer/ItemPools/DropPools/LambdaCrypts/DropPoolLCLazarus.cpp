#include "DropPoolLCLazarus.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/LambdaCrypts/CurrencyPoolLCGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/AlchemyPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/SmithingPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/PotionPoolTier5.h"
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

DropPoolLCLazarus::DropPoolLCLazarus(ValueMap& properties) : super(properties, DropPoolLCLazarus::PoolName, SampleMethod::Random, 1, 3, CurrencyPoolLCGeneric::create(properties),
	{
		AlchemyPoolTier5::create(SampleMethod::Random, 1, 2),
		SmithingPoolTier5::create(SampleMethod::Random, 1, 2),
	})
{
	this->addItemToPool(ItemChance::create(AncientKey::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(HeartOfShadow::create(), ItemChance::Probability::Guaranteed));
}

DropPoolLCLazarus::~DropPoolLCLazarus()
{
}
