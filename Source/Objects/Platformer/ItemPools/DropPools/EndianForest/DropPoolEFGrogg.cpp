#include "DropPoolEFGrogg.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/EndianForest/CurrencyPoolEFGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/AlchemyPoolT1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/CardPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/SmithingPoolT1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/PotionPoolTier1.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolEFGrogg::PoolName = "ef-grogg";

DropPoolEFGrogg* DropPoolEFGrogg::create(ValueMap& properties)
{
	DropPoolEFGrogg* instance = new DropPoolEFGrogg(properties);

	instance->autorelease();

	return instance;
}

DropPoolEFGrogg::DropPoolEFGrogg(ValueMap& properties) : super(properties, DropPoolEFGrogg::PoolName, SampleMethod::Unbounded, 1, 2, CurrencyPoolEFGeneric::create(properties),
	{
		CardPoolTier1::create(SampleMethod::Random, 0, 1),
		PotionPoolTier1::create(SampleMethod::Random, 0, 1)
	})
{
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Feather::create(), ItemChance::Probability::Guaranteed));
}

DropPoolEFGrogg::~DropPoolEFGrogg()
{
}
