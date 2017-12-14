#include "MenuSprite.h"

MenuSprite::MenuSprite(std::string spriteResource, std::string spriteSelectedResource) : MenuSprite(spriteResource, spriteSelectedResource, nullptr)
{
}

MenuSprite::MenuSprite(std::string spriteResource, std::string spriteSelectedResource, std::function<void(MenuSprite*)> onMouseClick)
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
	if (this->menuOnMouseClick != nullptr)
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
	if (this->menuOnMouseClick != nullptr)
	{
		if (Utils::Intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
		{
			this->menuOnMouseClick(this);
		}
	}
}
