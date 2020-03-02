#include "GorgonCinematicBehavior.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/Enemies/EndianForest/Gorgon.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string GorgonCinematicBehavior::MapKeyAttachedBehavior = "gorgon-cinematic";

GorgonCinematicBehavior* GorgonCinematicBehavior::create(GameObject* owner)
{
	GorgonCinematicBehavior* instance = new GorgonCinematicBehavior(owner);

	instance->autorelease();

	return instance;
}

GorgonCinematicBehavior::GorgonCinematicBehavior(GameObject* owner) : super(owner)
{
	this->gorgon = dynamic_cast<Gorgon*>(owner);

	if (this->gorgon == nullptr)
	{
		this->invalidate();
	}
}

GorgonCinematicBehavior::~GorgonCinematicBehavior()
{
}

void GorgonCinematicBehavior::onLoad()
{
	this->runGorgonLoop();
}

void GorgonCinematicBehavior::runGorgonLoop()
{
	if (this->gorgon == nullptr)
	{
		return;
	}

	this->gorgon->getAnimations()->clearAnimationPriority();

	this->gorgon->getAnimations()->playAnimation("AttackRebound", SmartAnimationNode::AnimationPlayMode::Callback, 1.0f, 0.25f, [=]()
	{
		this->gorgon->getAnimations()->clearAnimationPriority();

		this->gorgon->getAnimations()->playAnimation("AttackStrongRebound", SmartAnimationNode::AnimationPlayMode::Callback, 1.0f, 0.25f, [=]()
		{
			this->gorgon->getAnimations()->clearAnimationPriority();

			this->gorgon->getAnimations()->playAnimation("AttackChargeRebound", SmartAnimationNode::AnimationPlayMode::Callback, 1.0f, 0.25f, [=]()
			{
				this->runGorgonLoop();
			});
		});
	});
}