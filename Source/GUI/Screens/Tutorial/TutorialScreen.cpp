#include "TutorialScreen.h"

TutorialScreen::TutorialScreen()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->titleLabel = new MenuLabel("", Resources::Fonts_Marker_Felt, this->titleFontSize);
	this->infoLabel = new MenuLabel("", Resources::Fonts_Marker_Felt, this->titleFontSize);
	this->background = Sprite::create(Resources::Menus_TutorialMenu_TutorialSelect);
	this->mouse = new Mouse();

	this->titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - this->titleLabel->getContentSize().height / 2));
	this->infoLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 + this->infoLabel->getContentSize().width / 2, origin.y + visibleSize.height - 24));
	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->addChild(this->background);
	this->addChild(this->titleLabel);
	this->addChild(this->infoLabel);

	this->LoadNodes();

	this->addChild(this->mouse);
}

TutorialScreen::~TutorialScreen()
{
}

void TutorialScreen::OnMouseOver(TutorialItem* node)
{
	this->infoLabel->SetText(node->nodeMapName);
}

void TutorialScreen::LoadNodes()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float screenCenterX = origin.x + visibleSize.width / 2;
	float screenCenterY = origin.y + visibleSize.height / 2;

	std::function<void(TutorialItem*)> callback = CC_CALLBACK_1(TutorialScreen::OnMouseOver, this);

	this->tutorialButtons = new std::vector<MenuSprite*>();

	this->addChild(new TutorialItem(
		"Exact Value Scan",
		Resources::Menus_TutorialMenu_TutorialItem,
		Vec2(screenCenterX, screenCenterY + 480.0f),
		true,
		callback
	));

	this->addChild(new TutorialItem(
		"Unknown Value Scan",
		Resources::Menus_TutorialMenu_TutorialItem,
		Vec2(screenCenterX, screenCenterY + 320.0f),
		true,
		callback
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
		Director::getInstance()->replaceScene(new TitleScreen());
		break;
	}
}
