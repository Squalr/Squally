#include "RewardPoolLycan.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string RewardPoolLycan::PoolName = "lycan-reward";

RewardPoolLycan* RewardPoolLycan::create(ValueMap& properties)
{
	RewardPoolLycan* instance = new RewardPoolLycan(properties);

	instance->autorelease();

	return instance;
}

RewardPoolLycan::RewardPoolLycan(ValueMap& properties) : super(properties, RewardPoolLycan::PoolName, SampleMethod::Guarantee, 1, 1, nullptr,
	{
	})
{
	this->addItemToPool(ItemChance::create(WoodenSword::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(WoodenAxe::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(WoodenClub::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(WoodenWand::create(), ItemChance::Probability::VeryCommon));
}

RewardPoolLycan::~RewardPoolLycan()
{
}
