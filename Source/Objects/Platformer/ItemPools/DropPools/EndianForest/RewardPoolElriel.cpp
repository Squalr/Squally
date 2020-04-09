#include "RewardPoolElriel.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string RewardPoolElriel::PoolName = "elriel-reward";

RewardPoolElriel* RewardPoolElriel::create(ValueMap& properties)
{
	RewardPoolElriel* instance = new RewardPoolElriel(properties);

	instance->autorelease();

	return instance;
}

RewardPoolElriel::RewardPoolElriel(ValueMap& properties) : super(properties, RewardPoolElriel::PoolName, SampleMethod::Guarantee, 1, 1, nullptr,
	{
	})
{
	this->addItemToPool(ItemChance::create(GlowingPendant::create(), ItemChance::Probability::Guaranteed));
}

RewardPoolElriel::~RewardPoolElriel()
{
}
