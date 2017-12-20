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
	this->plasma = ParticleSystemQuad::create(Resources::Particles_BluePlasma);
	this->warp = ParticleSystemQuad::create(Resources::Particles_WarpPoint);
	this->swirl = ParticleSystemQuad::create(Resources::Particles_BlueSwirl);
	this->mouse = Mouse::create();

	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->plasma->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->warp->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->swirl->setPosition(Vec2(origin.x + visibleSize.width / 2 - 128.0f, origin.y + visibleSize.height / 2));
	this->tutorialWindow->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	//this->warp->setScale(15.0f);
	this->swirl->setScale(8.0f);

	// this->addChild(this->plasma);
	this->addChild(this->warp);
	this->addChild(this->swirl);

	this->addChild(this->background);
	this->addChild(this->tutorialWindow);

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
