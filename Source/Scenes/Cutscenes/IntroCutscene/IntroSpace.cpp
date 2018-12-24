#include "IntroSpace.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCLabel.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Dialogue/DialogueLabel.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Cutscenes/Objects/StarLayer.h"

#include "Resources/CutsceneResources.h"
#include "Resources/StringResources.h"

#include "Strings/Cutscenes/PressEscToSkip.h"

using namespace cocos2d;

const float IntroSpace::dialogueHeight = 256.0f;

const float IntroSpace::marsDelta = 1280.0f;
const float IntroSpace::weaverDelta = 1280.0f;
const float IntroSpace::earthDelta = 1280.0f;

IntroSpace* IntroSpace::create()
{
	IntroSpace* instance = new IntroSpace();

	instance->autorelease();

	return instance;
}

IntroSpace::IntroSpace()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->starLayer = StarLayer::create(Size(visibleSize.width * 2.0f, visibleSize.height));
	this->earth = Sprite::create(CutsceneResources::IntroSpace_Earth);
	this->mars = Sprite::create(CutsceneResources::IntroSpace_Mars);
	this->weavers = Node::create();
	this->weaver1 = SmartAnimationSequenceNode::create(CutsceneResources::IntroSpace_Weaver_0000);
	this->weaver2 = SmartAnimationSequenceNode::create(CutsceneResources::IntroSpace_Weaver_0000);
	this->weaver3 = SmartAnimationSequenceNode::create(CutsceneResources::IntroSpace_Weaver_0000);
	this->weaver4 = SmartAnimationSequenceNode::create(CutsceneResources::IntroSpace_Weaver_0000);
	this->weaver5 = SmartAnimationSequenceNode::create(CutsceneResources::IntroSpace_Weaver_0000);
	this->dialoguePlate = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, IntroSpace::dialogueHeight);
	this->dialogue = DialogueLabel::create(StringResources::Dialogue_CutsceneIntroSpace, LocalizedLabel::create(LocalizedLabel::FontStyle::Pixel, LocalizedLabel::FontSize::H3), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
	this->escapeLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Pixel, LocalizedLabel::FontSize::H3, LocaleStrings::PressEscToSkip::create(), Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->mars->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->earth->setAnchorPoint(Vec2(1.0f, 1.0f));
	this->weaver1->setScale(0.12f);
	this->weaver2->setScale(0.14f);
	this->weaver3->setScale(0.16f);
	this->weaver4->setScale(0.18f);
	this->weaver5->setScale(0.20f);

	this->addChild(this->starLayer);
	this->addChild(this->earth);
	this->addChild(this->mars);
	this->weavers->addChild(this->weaver1);
	this->weavers->addChild(this->weaver2);
	this->weavers->addChild(this->weaver3);
	this->weavers->addChild(this->weaver4);
	this->weavers->addChild(this->weaver5);
	this->addChild(this->weavers);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

IntroSpace::~IntroSpace()
{
}

void IntroSpace::onEnter()
{
	CutsceneClip::onEnter();

	this->weaver1->playAnimation(CutsceneResources::IntroSpace_Weaver_0000, 0.2f);
	this->weaver2->playAnimation(CutsceneResources::IntroSpace_Weaver_0000, 0.225f);
	this->weaver3->playAnimation(CutsceneResources::IntroSpace_Weaver_0000, 0.25f);
	this->weaver4->playAnimation(CutsceneResources::IntroSpace_Weaver_0000, 0.275f);
	this->weaver5->playAnimation(CutsceneResources::IntroSpace_Weaver_0000, 0.3f);

	this->runCutscene();
}

void IntroSpace::initializePositions()
{
	CutsceneClip::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->mars->setPosition(Vec2(64.0f + marsDelta, 48.0f));
	this->earth->setPosition(Vec2(visibleSize.width - 32.0f + earthDelta, visibleSize.height - 32.0f));
	this->weavers->setPositionX(weaverDelta);

	this->weaver1->setPosition(Vec2(visibleSize.width / 2.0f + 432.0f, visibleSize.height / 2.0f + 240.0f));
	this->weaver2->setPosition(Vec2(visibleSize.width / 2.0f + 384.0f, visibleSize.height / 2.0f + 224.0f));
	this->weaver3->setPosition(Vec2(visibleSize.width / 2.0f + 412.0f, visibleSize.height / 2.0f + 196.0f));
	this->weaver4->setPosition(Vec2(visibleSize.width / 2.0f + 368.0f, visibleSize.height / 2.0f + 188.0f));
	this->weaver5->setPosition(Vec2(visibleSize.width / 2.0f + 320.0f, visibleSize.height / 2.0f + 160.0f));

	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));
}

void IntroSpace::initializeListeners()
{
	CutsceneClip::initializeListeners();

	this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(IntroSpace::onDialogueShown, this));
}

void IntroSpace::onDialogueShown()
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
}

void IntroSpace::runCutscene()
{
	float duration = 5.0f;

	this->dialogue->showNextDialogue();

	CallFunc* scroll = CallFunc::create([=]() {
		this->earth->runAction(MoveTo::create(duration, this->earth->getPosition() - Vec2(IntroSpace::earthDelta, 0.0f)));
		this->weavers->runAction(MoveTo::create(duration, this->weavers->getPosition() - Vec2(IntroSpace::weaverDelta, 0.0f)));
		this->mars->runAction(MoveTo::create(duration, this->mars->getPosition() - Vec2(IntroSpace::marsDelta, 0.0f)));
	});

	this->runAction(Sequence::create(
		DelayTime::create(3.0f),
		scroll,
		nullptr
	));
}
