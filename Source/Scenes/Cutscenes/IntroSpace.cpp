#include "IntroSpace.h"

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

	this->weaver1->setScale(0.12);
	this->weaver2->setScale(0.14);
	this->weaver3->setScale(0.16);
	this->weaver4->setScale(0.18);
	this->weaver5->setScale(0.20);

	auto weaverFrames = GameUtils::getAllAnimationFiles(Resources::Cutscenes_IntroSpace_Weaver_0000);

	for (auto it = weaverFrames.begin(); it != weaverFrames.end(); it++)
	{
		this->weaver1Anim->addSpriteFrameWithFileName(*it);
		this->weaver2Anim->addSpriteFrameWithFileName(*it);
		this->weaver3Anim->addSpriteFrameWithFileName(*it);
		this->weaver4Anim->addSpriteFrameWithFileName(*it);
		this->weaver5Anim->addSpriteFrameWithFileName(*it);
	}

	this->weaver1->retain();
	this->weaver2->retain();
	this->weaver3->retain();
	this->weaver4->retain();
	this->weaver5->retain();

	this->addChild(InputManager::claimInstance());
	this->addChild(this->starLayer);
	this->addChild(this->earth);
	this->addChild(this->mars);
	this->addChild(this->weaver1);
	this->addChild(this->weaver2);
	this->addChild(this->weaver3);
	this->addChild(this->weaver4);
	this->addChild(this->weaver5);
}

IntroSpace::~IntroSpace()
{
}

void IntroSpace::onEnter()
{
	Cutscene::onEnter();

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

	this->scheduleUpdate();
	this->initializePositions();
	this->initializeListeners();
}

void IntroSpace::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->mars->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->mars->setPosition(Vec2(64.0f, 48.0f));
	this->earth->setAnchorPoint(Vec2(1.0f, 1.0f));
	this->earth->setPosition(Vec2(visibleSize.width - 32.0f, visibleSize.height - 32.0f));

	this->weaver1->setPosition(Vec2(visibleSize.width / 2.0f + 432.0f, visibleSize.height / 2.0f + 240.0f));
	this->weaver2->setPosition(Vec2(visibleSize.width / 2.0f + 384.0f, visibleSize.height / 2.0f + 224.0f));
	this->weaver3->setPosition(Vec2(visibleSize.width / 2.0f + 412.0f, visibleSize.height / 2.0f + 196.0f));
	this->weaver4->setPosition(Vec2(visibleSize.width / 2.0f + 368.0f, visibleSize.height / 2.0f + 188.0f));
	this->weaver5->setPosition(Vec2(visibleSize.width / 2.0f + 320.0f, visibleSize.height / 2.0f + 160.0f));
}

void IntroSpace::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void IntroSpace::update(float dt)
{
	FadeScene::update(dt);

	if (InputManager::getInstance()->isPressed(EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		this->endCutscene();
	}
}

void IntroSpace::endCutscene()
{
	NavigationEvents::loadMap(Resources::Maps_Isometric_Sanctum);
}
