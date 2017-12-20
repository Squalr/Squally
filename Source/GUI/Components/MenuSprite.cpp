#include "MenuSprite.h"

MenuSprite* MenuSprite::create(std::string spriteResource, std::string spriteSelectedResource, std::string spriteClickedResource)
{
	MenuSprite* menuSprite = new MenuSprite(spriteResource, spriteSelectedResource, spriteClickedResource);

	menuSprite->autorelease();

	return menuSprite;
}

MenuSprite::MenuSprite(std::string spriteResource, std::string spriteSelectedResource, std::string spriteClickedResource)
{
	this->menuOnMouseClick = nullptr;
	this->sprite = Sprite::create(spriteResource);
	this->spriteClicked = Sprite::create(spriteClickedResource);
	this->spriteSelected = Sprite::create(spriteSelectedResource);

	this->spriteClicked->setVisible(false);
	this->spriteSelected->setVisible(false);

	this->setContentSize(this->sprite->getContentSize());

	this->addChild(this->sprite);
	this->addChild(this->spriteClicked);
	this->addChild(this->spriteSelected);

}

MenuSprite::~MenuSprite()
{
}

void MenuSprite::SetClickCallback(std::function<void(MenuSprite*)> onMouseClick)
{
	this->menuOnMouseClick = onMouseClick;
}

void SetMouseOverSound(std::string soundResource)
{

}

void SetClickSound(std::string soundResource)
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
	mouseListener->onMouseUp = CC_CALLBACK_1(MenuSprite::OnMouseUp, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void MenuSprite::OnMouseMove(EventMouse* event)
{
	if (this->menuOnMouseClick != nullptr && this->isVisible())
	{
		if (Utils::Intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
		{
			if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
			{
				this->sprite->setVisible(false);
				this->spriteClicked->setVisible(true);
				this->spriteSelected->setVisible(false);
			}
			else
			{
				this->sprite->setVisible(false);
				this->spriteClicked->setVisible(false);
				this->spriteSelected->setVisible(true);
			}
		}
		else
		{
			this->sprite->setVisible(true);
			this->spriteClicked->setVisible(false);
			this->spriteSelected->setVisible(false);
		}
	}
}

void MenuSprite::OnMouseDown(EventMouse* event)
{
	if (Utils::Intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
	{
		this->sprite->setVisible(false);
		this->spriteClicked->setVisible(true);
		this->spriteSelected->setVisible(false);
	}
}

void MenuSprite::OnMouseUp(EventMouse* event)
{
	if (this->menuOnMouseClick != nullptr && this->isVisible())
	{
		if (Utils::Intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
		{
			this->menuOnMouseClick(this);
		}
	}
}
