#include "SquallyUploadMars.h"

#include "cocos/2d/CCLabel.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Dialogue/DialogueLabel.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Cutscenes/Objects/StarLayer.h"

#include "Resources/CutsceneResources.h"
#include "Resources/StringResources.h"

#include "Strings/Cutscenes/PressEscToSkip.h"

using namespace cocos2d;

const Vec2 SquallyUploadMars::panOffset = Vec2(-608.0f, 256.0f);

SquallyUploadMars* SquallyUploadMars::create()
{
	SquallyUploadMars* instance = new SquallyUploadMars();

	instance->autorelease();

	return instance;
}

SquallyUploadMars::SquallyUploadMars()
{
	this->dialogueCount = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background = Sprite::create(CutsceneResources::SquallyUploadMars_Scene);
	this->squally = Sprite::create(CutsceneResources::SquallyUploadMars_SquallyPixel);

	this->squally->setOpacity(0);
	this->background->setOpacity(0);

	this->dialogue = DialogueLabel::create(StringResources::Dialogue_CutsceneSquallyUploadMars, LocalizedLabel::create(LocalizedLabel::FontStyle::Pixel, LocalizedLabel::FontSize::H3), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
	
	this->dialoguePlate = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, 256.0f);
	this->escapeLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Pixel, LocalizedLabel::FontSize::H3, Strings::Cutscenes_PressEscToSkip::create(), Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));

	this->addChild(this->background);
	this->addChild(this->squally);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

SquallyUploadMars::~SquallyUploadMars()
{
}

void SquallyUploadMars::onEnter()
{
	CutsceneClip::onEnter();

	this->dialogue->showNextDialogue();

	this->runCutscene();
}

void SquallyUploadMars::initializePositions()
{
	CutsceneClip::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->squally->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));
}

void SquallyUploadMars::initializeListeners()
{
	CutsceneClip::initializeListeners();

	this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(SquallyUploadMars::onDialogueShown, this));
}

void SquallyUploadMars::runCutscene()
{
	const float duration = 1.5f;
	Vec2 start = this->squally->getPosition();
	Vec2 end = start + Vec2(0.0f, 64.0f);

	this->squally->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(duration, end)),
		EaseSineInOut::create(MoveTo::create(duration, start)),
		nullptr,
		nullptr
	)));
}

void SquallyUploadMars::runCutscenePt2()
{
	this->squally->runAction(FadeIn::create(1.0f));
}

void SquallyUploadMars::runCutscenePt3()
{
	this->squally->runAction(FadeOut::create(1.0f));

	this->background->runAction(Sequence::create(
		DelayTime::create(1.0f),
		FadeIn::create(1.0f),
		nullptr
	));
}

void SquallyUploadMars::onDialogueShown()
{
	this->dialogueCount++;

	this->dialogue->runAction(Sequence::create(
		DelayTime::create(2.0f),
		CallFunc::create([=]() {
			if (this->dialogueCount == 1)
			{
				this->runCutscenePt2();
			}

			if (this->dialogueCount == 2)
			{
				this->runCutscenePt3();
			}

			if (!this->dialogue->showNextDialogue())
			{
				this->dialogue->runAction(Sequence::create(
					DelayTime::create(5.0f),
					CallFunc::create([=]()
					{
						this->endCutsceneClip();
					}),
				nullptr));
			}
		}),
		nullptr
	));
}
