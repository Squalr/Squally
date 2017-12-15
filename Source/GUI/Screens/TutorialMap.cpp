#include "TutorialMap.h"

TutorialMap::TutorialMap()
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

TutorialMap::~TutorialMap()
{
}

void TutorialMap::OnMouseOver(MapNode* node)
{
	this->infoLabel->SetText(node->nodeMapName);
}

void TutorialMap::LoadNodes()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float screenCenterX = origin.x + visibleSize.width / 2;
	float screenCenterY = origin.y + visibleSize.height / 2;

	std::function<void(MapNode*)> callback = CC_CALLBACK_1(TutorialMap::OnMouseOver, this);

	this->addChild(new MapNode(
		"Exact Value Scan",
		Resources::Levels_Debug,
		Vec2(screenCenterX - 440.0f, screenCenterY + 280.0f),
		true,
		callback
	));

	this->addChild(new MapNode(
		"Unknown Value Scan",
		Resources::Levels_Debug,
		Vec2(screenCenterX - 400.0f, screenCenterY + 240.0f),
		true,
		callback
	));
}

void TutorialMap::onEnter()
{
	Scene::onEnter();

	this->InitializeListeners();
}

void TutorialMap::InitializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(TutorialMap::OnKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void TutorialMap::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->replaceScene(new TitleScreen());
		break;
	}
}
