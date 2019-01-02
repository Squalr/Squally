#include "SquallyUploadSpace.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Dialogue/DialogueLabel.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Cutscenes/Objects/StarLayer.h"

#include "Resources/CutsceneResources.h"
#include "Resources/StringResources.h"

#include "Strings/Cutscenes/PressEscToSkip.h"
#include "Strings/Generics/Constant.h"

using namespace cocos2d;

const Vec2 SquallyUploadSpace::panOffset = Vec2(-608.0f, 256.0f);

SquallyUploadSpace* SquallyUploadSpace::create()
{
	SquallyUploadSpace* instance = new SquallyUploadSpace();

	instance->autorelease();

	return instance;
}

SquallyUploadSpace::SquallyUploadSpace()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->starLayer = StarLayer::create(Size(visibleSize.width * 2.0f, visibleSize.height));
	this->mars = Sprite::create(CutsceneResources::IntroSpace_Mars);
	this->beam = Node::create();
	this->satellite = Sprite::create(CutsceneResources::SquallyUploadSpace_Satellite);
	this->dialogue = DialogueLabel::create(StringResources::Dialogue_CutsceneSquallyUploadSpace, LocalizedLabel::create(LocalizedLabel::FontStyle::Pixel, LocalizedLabel::FontSize::H3, Strings::Generics_Constant::create()), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));

	this->dialoguePlate = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, 256.0f);
	this->escapeLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Pixel, LocalizedLabel::FontSize::H3, Strings::Cutscenes_PressEscToSkip::create(), Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->mars->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->beam->setCascadeOpacityEnabled(true);
	this->beam->setOpacity(0);

	this->addChild(this->starLayer);
	this->addChild(this->mars);
	this->addChild(this->beam);
	this->addChild(this->satellite);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

SquallyUploadSpace::~SquallyUploadSpace()
{
}

void SquallyUploadSpace::onEnter()
{
	CutsceneClip::onEnter();

	this->dialogue->showNextDialogue();

	this->runCutscene();
}

void SquallyUploadSpace::initializePositions()
{
	CutsceneClip::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->mars->setPosition(Vec2(visibleSize.width / 2.0f - 128.0f, 48.0f));
	this->satellite->setPosition(Vec2(visibleSize.width / 2.0f + 64.0f, visibleSize.height / 2.0f + 128.0f));
	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));

	DrawNode* beam1a = DrawNode::create(4.0f);
	beam1a->drawLine(this->mars->getPosition() + Vec2(66.0f, this->mars->getContentSize().height / 2.0f + 46.0f), this->satellite->getPosition(), Color4F::GREEN);

	DrawNode* beam1b = DrawNode::create(2.0f);
	beam1b->drawLine(this->mars->getPosition() + Vec2(66.0f, this->mars->getContentSize().height / 2.0f + 46.0f), this->satellite->getPosition(), Color4F::BLUE);

	DrawNode* beam2a = DrawNode::create(4.0f);
	beam2a->drawLine(this->satellite->getPosition(), Vec2(visibleSize.width, visibleSize.height + 256.0f), Color4F::GREEN);

	DrawNode* beam2b = DrawNode::create(2.0f);
	beam2b->drawLine(this->satellite->getPosition(), Vec2(visibleSize.width, visibleSize.height + 256.0f), Color4F::BLUE);

	this->beam->addChild(beam1a);
	this->beam->addChild(beam1b);
	this->beam->addChild(beam2a);
	this->beam->addChild(beam2b);
}

void SquallyUploadSpace::initializeListeners()
{
	CutsceneClip::initializeListeners();

	this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(SquallyUploadSpace::onDialogueShown, this));
}

void SquallyUploadSpace::runCutscene()
{
	this->beam->runAction(Sequence::create(
		DelayTime::create(1.0f),
		FadeIn::create(0.2f),
		DelayTime::create(0.5f),
		FadeOut::create(0.2f),
		nullptr
	));
}

void SquallyUploadSpace::onDialogueShown()
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
