#include "RewardPoolHera.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string RewardPoolHera::MapKey = "reward-pool-hera";
const std::string RewardPoolHera::PoolName = "reward-pool-hera";

RewardPoolHera* RewardPoolHera::create(ValueMap& properties)
{
	RewardPoolHera* instance = new RewardPoolHera(properties);

	instance->autorelease();

	return instance;
}

RewardPoolHera::RewardPoolHera(ValueMap& properties) : super(properties, RewardPoolHera::PoolName, { })
{
	this->addItemToPool(ItemChance::create(ArchersHat::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(AcolytesCap::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(CopperHelm::create(), ItemChance::Probability::Guaranteed));
}

RewardPoolHera::~RewardPoolHera()
{
}

void RewardPoolHera::onEnter()
{
	super::onEnter(); 
}

void RewardPoolHera::initializePositions()
{
	super::initializePositions();
}

void RewardPoolHera::initializeListeners()
{
	super::initializeListeners();
}
