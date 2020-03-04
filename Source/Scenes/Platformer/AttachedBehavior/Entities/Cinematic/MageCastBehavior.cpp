#include "MageCastBehavior.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string MageCastBehavior::MapKeyAttachedBehavior = "mage-cast";

MageCastBehavior* MageCastBehavior::create(GameObject* owner)
{
	MageCastBehavior* instance = new MageCastBehavior(owner);

	instance->autorelease();

	return instance;
}

MageCastBehavior::MageCastBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

MageCastBehavior::~MageCastBehavior()
{
}

void MageCastBehavior::onLoad()
{
	this->entity->getAnimations()->playAnimation("AttackCastChannel", SmartAnimationNode::AnimationPlayMode::Repeat, 1.0f);
}
