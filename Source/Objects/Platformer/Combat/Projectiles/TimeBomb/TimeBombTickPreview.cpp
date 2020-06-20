#include "TimeBombTickPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

const int TimeBombTickPreview::MaxTick = 3;

TimeBombTickPreview* TimeBombTickPreview::create()
{
	TimeBombTickPreview* instance = new TimeBombTickPreview();

	instance->autorelease();

	return instance;
}

TimeBombTickPreview::TimeBombTickPreview()
{
	this->currentTick = TimeBombTickPreview::MaxTick;
	this->timeBomb = Sprite::create(ObjectResources::Traps_TimeBomb_BOMB);
	this->tickStr = ConstantString::create(std::to_string(this->currentTick));
	this->tick = this->createRegisterEqualsValueLabel(HackableCode::Register::zcx, false, this->tickStr);
	this->explosionAnim = SmartAnimationSequenceNode::create();
	this->elapsed = 0.0f;

	this->previewNode->addChild(this->timeBomb);
	this->previewNode->addChild(this->explosionAnim);
	this->assemblyTextNode->addChild(this->tick);
}

TimeBombTickPreview::~TimeBombTickPreview()
{
}

HackablePreview* TimeBombTickPreview::clone()
{
	return TimeBombTickPreview::create();
}

void TimeBombTickPreview::onEnter()
{
	super::onEnter();

	this->explosionAnim->setPosition(Vec2(0.0f, -16.0f));
	this->timeBomb->setPosition(Vec2(0.0f, -16.0f));

	this->scheduleUpdate();
}

void TimeBombTickPreview::initializePositions()
{
	super::initializePositions();
	
	this->tick->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - 48.0f));
}

void TimeBombTickPreview::update(float dt)
{
	super::update(dt);

	if (this->currentTick <= 0)
	{
		return;
	}

	this->elapsed += dt;

	if (this->elapsed >= 1.0f)
	{
		this->elapsed -= 1.0f;
		this->currentTick--;

		this->tickStr->setString(std::to_string(this->currentTick));

		if (this->currentTick <= 0)
		{
			this->timeBomb->setVisible(false);
			this->explosionAnim->playAnimation(FXResources::Explosion_Explosion_0000, 0.05f, true);

			this->runAction(Sequence::create(
				DelayTime::create(1.0f),
				CallFunc::create([=]()
				{
					this->timeBomb->setVisible(true);
					this->currentTick = TimeBombTickPreview::MaxTick;
					this->tickStr->setString(std::to_string(this->currentTick));
				}),
				nullptr
			));
		}
	}
}
