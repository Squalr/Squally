#include "IntroSpace.h"

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
	this->earth = Sprite::create(Resources::Cutscenes_IntroSpace_Earth);
	this->mars = Sprite::create(Resources::Cutscenes_IntroSpace_Mars);
	this->weavers = Node::create();
	this->weaver1 = Sprite::create();
	this->weaver2 = Sprite::create();
	this->weaver3 = Sprite::create();
	this->weaver4 = Sprite::create();
	this->weaver5 = Sprite::create();
	this->weaver1Anim = Animation::create();
	this->weaver2Anim = Animation::create();
	this->weaver3Anim = Animation::create();
	this->weaver4Anim = Animation::create();
	this->weaver5Anim = Animation::create();
	this->dialoguePlate = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, IntroSpace::dialogueHeight);
	this->dialogue = Dialogue::create(Resources::Strings_Dialogue_CutsceneIntroSpace, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
	this->escapeLabel = Label::create("Press esc to skip", Localization::getPixelFont(), 20.0f, Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->mars->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->earth->setAnchorPoint(Vec2(1.0f, 1.0f));
	this->weaver1->setScale(0.12f);
	this->weaver2->setScale(0.14f);
	this->weaver3->setScale(0.16f);
	this->weaver4->setScale(0.18f);
	this->weaver5->setScale(0.20f);

	auto weaverFrames = GameUtils::getAllAnimationFiles(Resources::Cutscenes_IntroSpace_Weaver_0000);

	for (auto it = weaverFrames.begin(); it != weaverFrames.end(); it++)
	{
		this->weaver1Anim->addSpriteFrameWithFileName(*it);
		this->weaver2Anim->addSpriteFrameWithFileName(*it);
		this->weaver3Anim->addSpriteFrameWithFileName(*it);
		this->weaver4Anim->addSpriteFrameWithFileName(*it);
		this->weaver5Anim->addSpriteFrameWithFileName(*it);
	}

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

	this->weaver1Anim->setDelayPerUnit(0.2f);
	this->weaver2Anim->setDelayPerUnit(0.225f);
	this->weaver3Anim->setDelayPerUnit(0.25f);
	this->weaver4Anim->setDelayPerUnit(0.275f);
	this->weaver5Anim->setDelayPerUnit(0.3f);

	this->weaver1->runAction(RepeatForever::create(Sequence::create(Animate::create(this->weaver1Anim), nullptr)));
	this->weaver2->runAction(RepeatForever::create(Sequence::create(Animate::create(this->weaver2Anim), nullptr)));
	this->weaver3->runAction(RepeatForever::create(Sequence::create(Animate::create(this->weaver3Anim), nullptr)));
	this->weaver4->runAction(RepeatForever::create(Sequence::create(Animate::create(this->weaver4Anim), nullptr)));
	this->weaver5->runAction(RepeatForever::create(Sequence::create(Animate::create(this->weaver5Anim), nullptr)));

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
