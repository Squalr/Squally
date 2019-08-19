#include "ScrappyBehaviorGroup.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Helpers/Scrappy/ScrappyMovementBehavior.h"

using namespace cocos2d;

const std::string ScrappyBehaviorGroup::MapKeyAttachedBehavior = "Scrappy";

ScrappyBehaviorGroup* ScrappyBehaviorGroup::create(GameObject* owner)
{
	ScrappyBehaviorGroup* instance = new ScrappyBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

ScrappyBehaviorGroup::ScrappyBehaviorGroup(GameObject* owner) : super(owner, {
	ScrappyMovementBehavior::create(owner),
	})
{
}

ScrappyBehaviorGroup::~ScrappyBehaviorGroup()
{
}

void ScrappyBehaviorGroup::onLoad()
{
}
