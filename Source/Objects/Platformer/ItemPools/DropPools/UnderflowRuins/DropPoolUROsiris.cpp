#include "DropPoolUROsiris.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/UnderflowRuins/CurrencyPoolURGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/AlchemyPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/CardPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/SmithingPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/PotionPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolUROsiris::PoolName = "ur-osiris";

DropPoolUROsiris* DropPoolUROsiris::create(ValueMap& properties)
{
	DropPoolUROsiris* instance = new DropPoolUROsiris(properties);

	instance->autorelease();

	return instance;
}

DropPoolUROsiris::DropPoolUROsiris(ValueMap& properties) : super(properties, DropPoolUROsiris::PoolName, SampleMethod::Unbounded, 1, 2, CurrencyPoolURGeneric::create(properties),
	{
		CardPoolTier2::create(SampleMethod::Random, 0, 1),
		PotionPoolTier2::create(SampleMethod::Random, 0, 1)
	})
{
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Feather::create(), ItemChance::Probability::Guaranteed));
}

DropPoolUROsiris::~DropPoolUROsiris()
{
}
