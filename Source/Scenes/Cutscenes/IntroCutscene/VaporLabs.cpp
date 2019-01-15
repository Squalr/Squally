#include "VaporLabs.h"

#include "cocos/2d/CCLabel.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/base/CCDirector.h"

//#include "Engine/Dialogue/DialogueLabel.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Cutscenes/Objects/StarLayer.h"

#include "Resources/CutsceneResources.h"
#include "Resources/StringResources.h"

#include "Strings/Cutscenes/PressEscToSkip.h"
#include "Strings/Generics/Constant.h"

using namespace cocos2d;

const Vec2 VaporLabs::panOffset = Vec2(-512.0f, 24.0f);

VaporLabs* VaporLabs::create()
{
	VaporLabs* instance = new VaporLabs();

	instance->autorelease();

	return instance;
}

VaporLabs::VaporLabs()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->contentLayer = Node::create();
	this->sky = LayerGradient::create(Color4B(70, 0, 131, 255), Color4B(64, 0, 64, 255), Vec2(0.0f, 1.0f));
	this->starLayer = StarLayer::create(Size(480.0f, 256.0f));
	this->cityView = Sprite::create(CutsceneResources::VaporLabs_CityView);
	this->background = Sprite::create(CutsceneResources::VaporLabs_Lab);
	this->console = Sprite::create(CutsceneResources::VaporLabs_Controls);
	this->monitor = Sprite::create(CutsceneResources::VaporLabs_Monitor);
	this->scientist = Sprite::create(CutsceneResources::VaporLabs_Scientist);
	this->siren = LayerColor::create(Color4B(255, 0, 0, 0));

	this->sky->setContentSize(Size(480.0f, 256.0f));

	this->dialoguePlate = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, 256.0f);
	//this->dialogue = DialogueLabel::create(StringResources::Dialogue_CutsceneVaporLabs, LocalizedLabel::create(LocalizedLabel::FontStyle::Pixel, LocalizedLabel::FontSize::H3, Strings::Generics_Constant::create()), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
	this->escapeLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Pixel, LocalizedLabel::FontSize::H3, Strings::Cutscenes_PressEscToSkip::create(), Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));

	this->contentLayer->addChild(this->sky);
	this->contentLayer->addChild(this->starLayer);
	this->contentLayer->addChild(this->cityView);
	this->contentLayer->addChild(this->background);
	this->contentLayer->addChild(this->console);
	this->contentLayer->addChild(this->scientist);
	this->contentLayer->addChild(this->monitor);
	this->addChild(this->contentLayer);
	this->addChild(this->siren);
	this->addChild(this->dialoguePlate);
	//this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

VaporLabs::~VaporLabs()
{
}

void VaporLabs::onEnter()
{
	CutsceneClip::onEnter();

	//this->dialogue->showNextDialogue();

	this->runCutscene();
}

void VaporLabs::initializePositions()
{
	CutsceneClip::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->contentLayer->setPosition(VaporLabs::panOffset);
	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->starLayer->setPosition(Vec2(visibleSize.width / 2.0f - this->starLayer->getContentSize().width / 2.0f, visibleSize.height / 2.0f - this->starLayer->getContentSize().height / 2.0f));
	this->sky->setPosition(Vec2(visibleSize.width / 2.0f - this->sky->getContentSize().width / 2.0f, visibleSize.height / 2.0f - this->sky->getContentSize().height / 2.0f));
	this->cityView->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->console->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 164.0f));
	this->scientist->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 188.0f));
	this->monitor->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 320.0f));

	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	//this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));
}

void VaporLabs::initializeListeners()
{
	CutsceneClip::initializeListeners();

	//this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(VaporLabs::onDialogueShown, this));
}

void VaporLabs::onDialogueShown()
{
	/*
	this->dialogue->runAction(Sequence::create(
		DelayTime::create(4.0f),
		CallFunc::create([=]() {
			if (!this->dialogue->showNextDialogue())
			{
				this->endCutsceneClip();
			}
		}),
		nullptr
	));*/
}

void VaporLabs::runCutscene()
{
	this->contentLayer->runAction(EaseSineInOut::create(MoveTo::create(4.0f, Vec2::ZERO)));

	const float fadeSpeed = 0.75f;
	const int endFade = 96;
	const int startFade = 16;

	this->siren->runAction(Sequence::create(
		DelayTime::create(2.5f),
		FadeTo::create(fadeSpeed, endFade),
		FadeTo::create(fadeSpeed, startFade),
		FadeTo::create(fadeSpeed, endFade),
		FadeTo::create(fadeSpeed, startFade),
		FadeTo::create(fadeSpeed, endFade),
		FadeTo::create(fadeSpeed, startFade),
		FadeTo::create(fadeSpeed, endFade),
		FadeTo::create(fadeSpeed, startFade),
		FadeTo::create(fadeSpeed, endFade),
		FadeTo::create(fadeSpeed, startFade),
		nullptr
	));
}
