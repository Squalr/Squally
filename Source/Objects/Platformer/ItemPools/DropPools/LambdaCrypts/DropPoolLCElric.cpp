#include "DropPoolLCElric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/EndianForest/CurrencyPoolEFGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/AlchemyPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/SmithingPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/PotionPoolTier5.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolLCElric::PoolName = "lc-elric";

DropPoolLCElric* DropPoolLCElric::create(ValueMap& properties)
{
	DropPoolLCElric* instance = new DropPoolLCElric(properties);

	instance->autorelease();

	return instance;
}

DropPoolLCElric::DropPoolLCElric(ValueMap& properties) : super(properties, DropPoolLCElric::PoolName, SampleMethod::Unbounded, 1, 2, CurrencyPoolEFGeneric::create(properties),
	{
		AlchemyPoolTier5::create(SampleMethod::Random, 1, 2),
		SmithingPoolTier5::create(SampleMethod::Random, 1, 2),
		// PotionPoolTier5::create(SampleMethod::Random, 0, 1),
	})
{
	this->addItemToPool(ItemChance::create(RustyKey::create(), ItemChance::Probability::Guaranteed));
}

DropPoolLCElric::~DropPoolLCElric()
{
}
