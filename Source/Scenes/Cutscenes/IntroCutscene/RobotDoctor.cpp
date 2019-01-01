#include "RobotDoctor.h"

#include "cocos/2d/CCLabel.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"
#include "cocos/math/Vec2.h"

#include "Engine/Dialogue/DialogueLabel.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/CutsceneResources.h"
#include "Resources/StringResources.h"

#include "Strings/Cutscenes/PressEscToSkip.h"

using namespace cocos2d;

const Vec2 RobotDoctor::panOffset = Vec2(-608.0f, 256.0f);

RobotDoctor* RobotDoctor::create(RobotDoctorScene robotDoctorScene)
{
	RobotDoctor* instance = new RobotDoctor(robotDoctorScene);

	instance->autorelease();

	return instance;
}

RobotDoctor::RobotDoctor(RobotDoctorScene robotDoctorScene)
{
	this->activeScene = robotDoctorScene;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background = Sprite::create(CutsceneResources::RobotDoctor_Background);
	this->bed = Sprite::create(CutsceneResources::RobotDoctor_Bed);

	switch (this->activeScene)
	{
		default:
		case RobotDoctorScene::Intro:
		{
			this->robot = Sprite::create(CutsceneResources::RobotDoctor_Doctor);
			this->dialogue = DialogueLabel::create(StringResources::Dialogue_CutsceneRobotDoctor, LocalizedLabel::create(LocalizedLabel::FontStyle::Pixel, LocalizedLabel::FontSize::H3), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
			break;
		}
		case RobotDoctorScene::Singularity:
		{
			this->robot = Sprite::create(CutsceneResources::RobotDoctor_DoctorEvil);
			this->dialogue = DialogueLabel::create(StringResources::Dialogue_CutsceneRobotDoctorSingularity, LocalizedLabel::create(LocalizedLabel::FontStyle::Pixel, LocalizedLabel::FontSize::H3), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
			break;
		}
	}

	this->dialoguePlate = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, 256.0f);
	this->escapeLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Pixel, LocalizedLabel::FontSize::H3, Strings::Cutscenes_PressEscToSkip::create(), Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));

	this->addChild(this->background);
	this->addChild(this->robot);
	this->addChild(this->bed);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

RobotDoctor::~RobotDoctor()
{
}

void RobotDoctor::onEnter()
{
	CutsceneClip::onEnter();

	this->dialogue->showNextDialogue();

	const float floatOffset = 16.0f;
	const float floatDuration = 2.0f;
	Vec2 initialPosition = this->robot->getPosition();

	this->robot->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(floatDuration, initialPosition + Vec2(0.0f, floatOffset)),
		MoveTo::create(floatDuration, initialPosition),
		nullptr
	)));
}

void RobotDoctor::initializePositions()
{
	CutsceneClip::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->robot->setPosition(Vec2(visibleSize.width / 2.0f + 24.0f, visibleSize.height / 2.0f + 96.0f));
	this->bed->setPosition(Vec2(visibleSize.width / 2.0f + 224.0f, visibleSize.height / 2.0f + 8.0f));
	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));
}

void RobotDoctor::initializeListeners()
{
	CutsceneClip::initializeListeners();

	this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(RobotDoctor::onDialogueShown, this));
}

void RobotDoctor::onDialogueShown()
{
	switch (this->activeScene)
	{
		default:
		case RobotDoctorScene::Intro:
		{
			this->dialogue->runAction(Sequence::create(
				DelayTime::create(3.0f),
				CallFunc::create([=]() {
					if (!this->dialogue->showNextDialogue())
					{
						this->endCutsceneClip();
					}
				}),
				nullptr
				));
			break;
		}
		case RobotDoctorScene::Singularity:
		{
			this->dialogue->runAction(Sequence::create(
				DelayTime::create(3.0f),
				CallFunc::create([=]() {
					if (!this->dialogue->showNextDialogue())
					{
						this->endCutsceneClip();
					}
				}),
				nullptr
				));
			break;
		}
	}
}
