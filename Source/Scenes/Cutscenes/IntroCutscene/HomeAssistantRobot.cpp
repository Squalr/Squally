#include "HomeAssistantRobot.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCLabel.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Dialogue/DialogueLabel.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/CutsceneResources.h"
#include "Resources/StringResources.h"

#include "Strings/Cutscenes/PressEscToSkip.h"

using namespace cocos2d;

const Vec2 HomeAssistantRobot::panOffset = Vec2(-608.0f, 256.0f);

HomeAssistantRobot* HomeAssistantRobot::create(HomeAssistantRobotScene homeAssistantRobotScene)
{
	HomeAssistantRobot* instance = new HomeAssistantRobot(homeAssistantRobotScene);

	instance->autorelease();

	return instance;
}

HomeAssistantRobot::HomeAssistantRobot(HomeAssistantRobotScene homeAssistantRobotScene)
{
	this->activeScene = homeAssistantRobotScene;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background = Sprite::create(CutsceneResources::HomeAssistant_Kitchen);
	this->brokenPlate = Sprite::create(CutsceneResources::HomeAssistant_BrokenPlate);

	switch (this->activeScene)
	{
		default:
		case HomeAssistantRobotScene::Intro:
		{
			this->robot = Sprite::create(CutsceneResources::HomeAssistant_Robot);
			this->dialogue = DialogueLabel::create(StringResources::Dialogue_CutsceneHomeAssistantRobot, LocalizedLabel::create(LocalizedLabel::FontStyle::Pixel, LocalizedLabel::FontSize::H3), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
			this->brokenPlate->setVisible(false);
			break;
		}
		case HomeAssistantRobotScene::Singularity:
		{
			this->robot = Sprite::create(CutsceneResources::HomeAssistant_RobotEvil);
			this->dialogue = DialogueLabel::create(StringResources::Dialogue_CutsceneHomeAssistantRobotSingularity, LocalizedLabel::create(LocalizedLabel::FontStyle::Pixel, LocalizedLabel::FontSize::H3), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
			break;
		}
	}

	this->dialoguePlate = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, 256.0f);
	this->escapeLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Pixel, LocalizedLabel::FontSize::H3, LocaleStrings::PressEscToSkip::create(), Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));

	this->addChild(this->background);
	this->addChild(this->robot);
	this->addChild(this->brokenPlate);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

HomeAssistantRobot::~HomeAssistantRobot()
{
}

void HomeAssistantRobot::onEnter()
{
	CutsceneClip::onEnter();

	this->dialogue->showNextDialogue();

	const float duration = 1.5f;
	Vec2 start = this->robot->getPosition();
	Vec2 end = start + Vec2(0.0f, 32.0f);

	this->robot->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(duration, end)),
		EaseSineInOut::create(MoveTo::create(duration, start)),
		nullptr,
		nullptr
	)));
}

void HomeAssistantRobot::initializePositions()
{
	CutsceneClip::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->robot->setPosition(Vec2(visibleSize.width / 2.0f - 420.0f, visibleSize.height / 2.0f - 96.0f));
	this->brokenPlate->setPosition(Vec2(visibleSize.width / 2.0f - 320.0f, visibleSize.height / 2.0f - 432.0f));
	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));
}

void HomeAssistantRobot::initializeListeners()
{
	CutsceneClip::initializeListeners();

	this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(HomeAssistantRobot::onDialogueShown, this));
}

void HomeAssistantRobot::onDialogueShown()
{
	switch (this->activeScene)
	{
		default:
		case HomeAssistantRobotScene::Intro:
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
		case HomeAssistantRobotScene::Singularity:
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
