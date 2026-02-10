#include "MineWinch.h"

#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "2d/CCActionEase.h"
#include "2d/CCSprite.h"
#include "base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MineWinch::MapKey = "winch";

MineWinch* MineWinch::create(ValueMap& properties)
{
	MineWinch* instance = new MineWinch(properties);
	
	instance->autorelease();

	return instance;
}

MineWinch::MineWinch(ValueMap& properties) : super(properties)
{
	this->mineClawAnimations = SmartAnimationNode::create(ObjectResources::Decor_Winch_Animations);

	this->mineClawAnimations->setPositionY(-GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat() / 2.0f);

	this->addChild(this->mineClawAnimations);
}

MineWinch::~MineWinch()
{
}

void MineWinch::onEnter()
{
	super::onEnter();

	this->runAnimation();
}

void MineWinch::initializePositions()
{
	super::initializePositions();
}

void MineWinch::initializeListeners()
{
	super::initializeListeners();
}

void MineWinch::runAnimation()
{
	this->mineClawAnimations->clearAnimationPriority();
	this->mineClawAnimations->playAnimation("LowerAndRaise", SmartAnimationNode::AnimationPlayMode::Callback, SmartAnimationNode::AnimParams(), [=]()
	{
		this->runAction(Sequence::create(
			DelayTime::create(RandomHelper::random_real(1.0f, 5.0f)),
			CallFunc::create([=]()
			{
				this->runAnimation();
			}),
			nullptr
		));

		this->mineClawAnimations->clearAnimationPriority();
		this->mineClawAnimations->playAnimation();
	});
}
