#include "TutorialScreen.h"

TutorialScreen * TutorialScreen::create()
{
	TutorialScreen* tutorialScreen = new TutorialScreen();

	tutorialScreen->autorelease();

	return tutorialScreen;
}

TutorialScreen::TutorialScreen()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->background = Sprite::create(Resources::Menus_TutorialMenu_Background);
	this->tutorialWindow = Sprite::create(Resources::Menus_TutorialMenu_TutorialSelect);

	this->floatingBox1 = Sprite::create(Resources::Menus_TutorialMenu_ObjectBox1);
	this->floatingBox2 = Sprite::create(Resources::Menus_TutorialMenu_ObjectBox2);
	this->floatingMisc1 = Sprite::create(Resources::Menus_TutorialMenu_ObjectSci1);
	this->floatingMisc2 = Sprite::create(Resources::Menus_TutorialMenu_ObjectSci2);
	this->floatingMisc3 = Sprite::create(Resources::Menus_TutorialMenu_ObjectSci3);
	this->floatingObelisk1 = Sprite::create(Resources::Menus_TutorialMenu_ObjectObelisk1);
	this->floatingObeliskParent = Sprite::create(Resources::Menus_TutorialMenu_ObjectObeliskChildren);
	this->floatingObeliskChild1 = Sprite::create(Resources::Menus_TutorialMenu_ObjectObeliskChildren_01);
	this->floatingObeliskChild2 = Sprite::create(Resources::Menus_TutorialMenu_ObjectObeliskChildren_02);
	this->floatingObeliskChild3 = Sprite::create(Resources::Menus_TutorialMenu_ObjectObeliskChildren_03);
	this->floatingObeliskChild4 = Sprite::create(Resources::Menus_TutorialMenu_ObjectObeliskChildren_04);
	this->floatingRocks2 = Sprite::create(Resources::Menus_TutorialMenu_ObjectRocks2);

	this->nether = ParticleSystemQuad::create(Resources::Particles_BlueNether);
	this->swirl = ParticleSystemQuad::create(Resources::Particles_BlueStarCircle);
	this->mouse = Mouse::create();

	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->nether->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->swirl->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->floatingBox1->setPosition(Vec2(origin.x + visibleSize.width / 2 + 640.0f, origin.y + visibleSize.height / 2 + 420.0f));
	this->floatingBox2->setPosition(Vec2(origin.x + visibleSize.width / 2 - 500.0f, origin.y + visibleSize.height / 2 + 64.0f));
	this->floatingMisc1->setPosition(Vec2(origin.x + visibleSize.width / 2 + 256.0f, origin.y + visibleSize.height / 2 + 320.0f));
	this->floatingMisc2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 540.0f, origin.y + visibleSize.height / 2));
	this->floatingMisc3->setPosition(Vec2(origin.x + visibleSize.width / 2 - 640.0f, origin.y + visibleSize.height / 2 + 420.0f));
	this->floatingObelisk1->setPosition(Vec2(origin.x + visibleSize.width / 2 - 196.0f, origin.y + visibleSize.height / 2 - 320.0f));
	this->floatingObeliskParent->setPosition(Vec2(origin.x + visibleSize.width / 2 - 240.0f, origin.y + visibleSize.height / 2 + 352.0f));
	this->floatingObeliskChild1->setPosition(Vec2(origin.x + visibleSize.width / 2 - 240.0f, origin.y + visibleSize.height / 2 + 352.0f));
	this->floatingObeliskChild2->setPosition(Vec2(origin.x + visibleSize.width / 2 - 240.0f, origin.y + visibleSize.height / 2 + 352.0f));
	this->floatingObeliskChild3->setPosition(Vec2(origin.x + visibleSize.width / 2 - 240.0f, origin.y + visibleSize.height / 2 + 352.0f));
	this->floatingObeliskChild4->setPosition(Vec2(origin.x + visibleSize.width / 2 - 240.0f, origin.y + visibleSize.height / 2 + 352.0f));
	this->floatingRocks2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 240.0f, origin.y + visibleSize.height / 2 - 272.0f));

	this->tutorialWindow->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	//this->addChild(this->background);
	this->addChild(this->nether);
	this->addChild(this->swirl);

	this->addChild(this->floatingBox1);
	this->addChild(this->floatingBox2);
	this->addChild(this->floatingMisc1);
	this->addChild(this->floatingMisc2);
	this->addChild(this->floatingMisc3);
	this->addChild(this->floatingObelisk1);
	this->addChild(this->floatingObeliskChild1);
	this->addChild(this->floatingObeliskChild3);
	this->addChild(this->floatingObeliskParent);
	this->addChild(this->floatingObeliskChild2);
	this->addChild(this->floatingObeliskChild4);
	this->addChild(this->floatingRocks2);

	this->addChild(this->tutorialWindow);

	this->LoadNodes();

	this->addChild(this->mouse);

	this->InitializeMovement();
}

TutorialScreen::~TutorialScreen()
{
}

void TutorialScreen::LoadNodes()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float screenCenterX = origin.x + visibleSize.width / 2;
	float screenCenterY = origin.y + visibleSize.height / 2;

	this->tutorialButtons = new std::vector<MenuSprite*>();

	this->addChild(TutorialItem::create(
		"Exact Value Scan I",
		Resources::Levels_Debug,
		Vec2(screenCenterX, screenCenterY + 168.0f - 12.0f)
	));

	this->addChild(TutorialItem::create(
		"Exact Value Scan II",
		Resources::Levels_Debug,
		Vec2(screenCenterX, screenCenterY + 72.0f - 12.0f * 2)
	));

	this->addChild(TutorialItem::create(
		"Unknown Value Scan",
		Resources::Levels_Debug,
		Vec2(screenCenterX, screenCenterY - 24.0f - 12.0f * 3)
	));

	this->addChild(TutorialItem::create(
		"Data Types - Float",
		Resources::Levels_Debug,
		Vec2(screenCenterX, screenCenterY - 120.0f - 12.0f * 4)
	));
}

void TutorialScreen::InitializeMovement()
{
	// Background shift
	float backgroundDistanceX01 = 64.0f;
	float backgroundDistanceX02 = -48.0f;
	float backgroundDistanceX03 = 8.0f;
	float backgroundDistanceX04 = -24.0f;
	float backgroundDistanceX05 = -32.0f;
	float backgroundDistanceX06 = -32.0f;

	float backgroundDistanceY01 = -8.0f;
	float backgroundDistanceY02 = 8.0f;
	float backgroundDistanceY03 = -8.0f;
	float backgroundDistanceY04 = 8.0f;
	float backgroundDistanceY05 = -8.0f;
	float backgroundDistanceY06 = 8.0f;

	float backgroundSpeedX = 7.0f;
	float backgroundSpeedY = 5.0f;

	FiniteTimeAction* shiftLeft01 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(backgroundDistanceX01, 0.0f)));
	FiniteTimeAction* shiftRight01 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(-backgroundDistanceX01, 0.0f)));
	FiniteTimeAction* shiftUp01 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, backgroundDistanceY01)));
	FiniteTimeAction* shiftDown01 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, -backgroundDistanceY01)));

	FiniteTimeAction* shiftLeft02 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(backgroundDistanceX02, 0.0f)));
	FiniteTimeAction* shiftRight02 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(-backgroundDistanceX02, 0.0f)));
	FiniteTimeAction* shiftUp02 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, backgroundDistanceY02)));
	FiniteTimeAction* shiftDown02 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, -backgroundDistanceY02)));

	FiniteTimeAction* shiftLeft03 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(backgroundDistanceX03, 0.0f)));
	FiniteTimeAction* shiftRight03 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(-backgroundDistanceX03, 0.0f)));
	FiniteTimeAction* shiftUp03 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, backgroundDistanceY03)));
	FiniteTimeAction* shiftDown03 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, -backgroundDistanceY03)));

	FiniteTimeAction* shiftLeft04 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(backgroundDistanceX04, 0.0f)));
	FiniteTimeAction* shiftRight04 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(-backgroundDistanceX04, 0.0f)));
	FiniteTimeAction* shiftUp04 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, backgroundDistanceY04)));
	FiniteTimeAction* shiftDown04 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, -backgroundDistanceY04)));

	FiniteTimeAction* shiftLeft05 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(backgroundDistanceX05, 0.0f)));
	FiniteTimeAction* shiftRight05 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(-backgroundDistanceX05, 0.0f)));
	FiniteTimeAction* shiftUp05 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, backgroundDistanceY05)));
	FiniteTimeAction* shiftDown05 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, -backgroundDistanceY05)));

	FiniteTimeAction* shiftLeft06 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(backgroundDistanceX06, 0.0f)));
	FiniteTimeAction* shiftRight06 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(-backgroundDistanceX06, 0.0f)));
	FiniteTimeAction* shiftUp06 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, backgroundDistanceY06)));
	FiniteTimeAction* shiftDown06 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, -backgroundDistanceY06)));

	this->floatingBox1->runAction(RepeatForever::create(Sequence::create(shiftLeft01, shiftRight01, nullptr)));
	this->floatingBox2->runAction(RepeatForever::create(Sequence::create(shiftUp01, shiftDown01, nullptr)));
	this->floatingMisc1->runAction(RepeatForever::create(Sequence::create(shiftLeft02, shiftRight02, nullptr)));
	this->floatingMisc2->runAction(RepeatForever::create(Sequence::create(shiftUp02, shiftDown02, nullptr)));
	this->floatingMisc3->runAction(RepeatForever::create(Sequence::create(shiftLeft03, shiftRight03, nullptr)));
	this->floatingObelisk1->runAction(RepeatForever::create(Sequence::create(shiftUp03, shiftDown03, nullptr)));
	this->floatingObeliskChild1->runAction(RepeatForever::create(Sequence::create(shiftLeft04, shiftRight04, nullptr)));
	this->floatingObeliskChild3->runAction(RepeatForever::create(Sequence::create(shiftUp04, shiftDown04, nullptr)));
	this->floatingObeliskParent->runAction(RepeatForever::create(Sequence::create(shiftLeft05, shiftRight05, nullptr)));
	this->floatingObeliskChild2->runAction(RepeatForever::create(Sequence::create(shiftUp05, shiftDown05, nullptr)));
	this->floatingObeliskChild4->runAction(RepeatForever::create(Sequence::create(shiftLeft06, shiftRight06, nullptr)));
	this->floatingRocks2->runAction(RepeatForever::create(Sequence::create(shiftUp06, shiftDown06, nullptr)));
}

void TutorialScreen::onEnter()
{
	Scene::onEnter();

	this->InitializeListeners();
}

void TutorialScreen::InitializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(TutorialScreen::OnKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void TutorialScreen::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->replaceScene(TitleScreen::create());
		break;
	}
}
