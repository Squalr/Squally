#include "RewardPoolLiana.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string RewardPoolLiana::PoolName = "liana-reward";

RewardPoolLiana* RewardPoolLiana::create(ValueMap& properties)
{
	RewardPoolLiana* instance = new RewardPoolLiana(properties);

	instance->autorelease();

	return instance;
}

RewardPoolLiana::RewardPoolLiana(ValueMap& properties) : super(properties, RewardPoolLiana::PoolName, SampleMethod::Guarantee, 2, 2, nullptr,
	{
	})
{
	this->addItemToPool(ItemChance::create(WoodenSword::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(WoodenAxe::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(WoodenClub::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(WoodenWand::create(), ItemChance::Probability::VeryCommon));

	this->addItemToPool(ItemChance::create(GlowingPendant::create(), ItemChance::Probability::Guaranteed));
}

RewardPoolLiana::~RewardPoolLiana()
{
}
