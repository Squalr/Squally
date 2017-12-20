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
	this->floatingDiamonds1 = Sprite::create(Resources::Menus_TutorialMenu_ObjectDiamonds1);
	this->floatingRocks1 = Sprite::create(Resources::Menus_TutorialMenu_ObjectRocks1);
	this->floatingRocks2 = Sprite::create(Resources::Menus_TutorialMenu_ObjectRocks2);

	this->plasma = ParticleSystemQuad::create(Resources::Particles_BluePlasma);
	this->warp = ParticleSystemQuad::create(Resources::Particles_WarpPoint);
	this->swirl = ParticleSystemQuad::create(Resources::Particles_BlueSwirl);
	this->mouse = Mouse::create();

	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->plasma->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->warp->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->swirl->setPosition(Vec2(origin.x + visibleSize.width / 2 - 256.0f, origin.y + visibleSize.height / 2));

	this->floatingBox1->setPosition(Vec2(origin.x + visibleSize.width / 2 + 640.0f, origin.y + visibleSize.height / 2 + 420.0f));
	this->floatingBox2->setPosition(Vec2(origin.x + visibleSize.width / 2 - 500.0f, origin.y + visibleSize.height / 2 + 64.0f));
	this->floatingMisc1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 320.0f));
	this->floatingMisc2->setPosition(Vec2(origin.x + visibleSize.width / 2 - 680.0f, origin.y + visibleSize.height / 2 - 320.0f));
	this->floatingMisc3->setPosition(Vec2(origin.x + visibleSize.width / 2 + 540.0f, origin.y + visibleSize.height / 2));
	this->floatingObelisk1->setPosition(Vec2(origin.x + visibleSize.width / 2 + 140.0f, origin.y + visibleSize.height / 2 - 240.0f));
	this->floatingObeliskParent->setPosition(Vec2(origin.x + visibleSize.width / 2 - 320.0f, origin.y + visibleSize.height / 2 + 320.0f));
	this->floatingObeliskChild1->setPosition(Vec2(origin.x + visibleSize.width / 2 - 320.0f, origin.y + visibleSize.height / 2 + 320.0f));
	this->floatingObeliskChild2->setPosition(Vec2(origin.x + visibleSize.width / 2 - 320.0f, origin.y + visibleSize.height / 2 + 320.0f));
	this->floatingObeliskChild3->setPosition(Vec2(origin.x + visibleSize.width / 2 - 320.0f, origin.y + visibleSize.height / 2 + 320.0f));
	this->floatingObeliskChild4->setPosition(Vec2(origin.x + visibleSize.width / 2 - 320.0f, origin.y + visibleSize.height / 2 + 320.0f));
	this->floatingDiamonds1->setPosition(Vec2(origin.x + visibleSize.width / 2 - 640.0f, origin.y + visibleSize.height / 2 + 420.0f));
	this->floatingRocks1->setPosition(Vec2(origin.x + visibleSize.width / 2 + 640.0f, origin.y + visibleSize.height / 2 + 420.0f));
	this->floatingRocks2->setPosition(Vec2(origin.x + visibleSize.width / 2 - 196.0f, origin.y + visibleSize.height / 2 - 320.0f));

	this->tutorialWindow->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	//this->warp->setScale(15.0f);
	this->swirl->setScale(4.0f);

	// this->addChild(this->plasma);
	// this->addChild(this->warp);
	// this->addChild(this->swirl);

	// this->addChild(this->background);

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
	//this->addChild(this->floatingDiamonds1);
	//this->addChild(this->floatingRocks1);
	this->addChild(this->floatingRocks2);

	// this->addChild(this->tutorialWindow);

	this->LoadNodes();

	this->addChild(this->mouse);
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
