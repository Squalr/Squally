#include "DropPoolLCKingZul.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/LambdaCrypts/CurrencyPoolLCGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/AlchemyPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/CardPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/SmithingPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/PotionPoolTier5.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolLCKingZul::PoolName = "lc-king-zul";

DropPoolLCKingZul* DropPoolLCKingZul::create(ValueMap& properties)
{
	DropPoolLCKingZul* instance = new DropPoolLCKingZul(properties);

	instance->autorelease();

	return instance;
}

DropPoolLCKingZul::DropPoolLCKingZul(ValueMap& properties) : super(properties, DropPoolLCKingZul::PoolName, SampleMethod::Random, 1, 2, CurrencyPoolCVGeneric::create(properties),
	{
		CardPoolTier5::create(SampleMethod::Random, 0, 1),
		AlchemyPoolTier5::create(SampleMethod::Random, 1, 2),
		SmithingPoolTier5::create(SampleMethod::Random, 1, 2),
	})
{
	this->addItemToPool(ItemChance::create(HellGateCrystal::create(), ItemChance::Probability::Guaranteed));
}

DropPoolLCKingZul::~DropPoolLCKingZul()
{
}
