#include "MenuSprite.h"

MenuSprite* MenuSprite::create(std::string spriteResource, std::string spriteSelectedResource, std::string spriteDownResource)
{
	MenuSprite* node = new MenuSprite(spriteResource, spriteSelectedResource, spriteDownResource);

	node->autorelease();

	return node;
}

MenuSprite* MenuSprite::create(std::string spriteResource, std::string spriteSelectedResource, std::string spriteDownResource, std::function<void(MenuSprite*)> onMouseClick)
{
	MenuSprite* node = new MenuSprite(spriteResource, spriteSelectedResource, spriteDownResource, onMouseClick);

	node->autorelease();

	return node;
}

MenuSprite::MenuSprite(std::string spriteResource, std::string spriteSelectedResource, std::string spriteDownResource) : MenuSprite(spriteResource, spriteSelectedResource, spriteDownResource, nullptr)
{
}

MenuSprite::MenuSprite(std::string spriteResource, std::string spriteSelectedResource, std::string spriteDownResource, std::function<void(MenuSprite*)> onMouseClick)
{
	this->menuOnMouseClick = onMouseClick;

	this->sprite = Sprite::create(spriteResource);
	this->spriteSelected = Sprite::create(spriteSelectedResource);

	this->spriteSelected->setVisible(false);

	this->setContentSize(this->sprite->getContentSize());

	this->addChild(this->sprite);
	this->addChild(this->spriteSelected);
}

MenuSprite::~MenuSprite()
{
}

void MenuSprite::onEnter()
{
	Node::onEnter();

	this->InitializeListeners();
}

void MenuSprite::InitializeListeners()
{
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = CC_CALLBACK_1(MenuSprite::OnMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MenuSprite::OnMouseDown, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void MenuSprite::OnMouseMove(EventMouse* event)
{
	if (this->menuOnMouseClick != nullptr && this->isVisible())
	{
		if (Utils::Intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
		{
			this->sprite->setVisible(false);
			this->spriteSelected->setVisible(true);
		}
		else
		{
			this->sprite->setVisible(true);
			this->spriteSelected->setVisible(false);
		}
	}
}

void MenuSprite::OnMouseDown(EventMouse* event)
{
	if (this->menuOnMouseClick != nullptr && this->isVisible())
	{
		if (Utils::Intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
		{
			this->menuOnMouseClick(this);
		}
	}
}
