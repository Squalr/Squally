#include "FlyBotBehaviorGroup.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Helpers/FlyBot/FlyBotMovementBehavior.h"

using namespace cocos2d;

const std::string FlyBotBehaviorGroup::MapKeyAttachedBehavior = "flybot";

FlyBotBehaviorGroup* FlyBotBehaviorGroup::create(GameObject* owner)
{
	FlyBotBehaviorGroup* instance = new FlyBotBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

FlyBotBehaviorGroup::FlyBotBehaviorGroup(GameObject* owner) : super(owner, {
	FlyBotMovementBehavior::create(owner),
	})
{
}

FlyBotBehaviorGroup::~FlyBotBehaviorGroup()
{
}

void FlyBotBehaviorGroup::onLoad()
{
}
