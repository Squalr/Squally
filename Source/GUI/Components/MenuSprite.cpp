#include "MenuSprite.h"

MenuSprite* MenuSprite::create(std::string spriteNormal, std::string spriteSelectedResource, std::string spriteClickedResource)
{
	return MenuSprite::create(Sprite::create(spriteNormal), Sprite::create(spriteSelectedResource), Sprite::create(spriteClickedResource));
}

MenuSprite* MenuSprite::create(Node* spriteNormal, std::string spriteSelectedResource, std::string spriteClickedResource)
{
	MenuSprite* menuSprite = new MenuSprite(spriteNormal, Sprite::create(spriteSelectedResource), Sprite::create(spriteClickedResource));

	menuSprite->autorelease();

	return menuSprite;
}

MenuSprite* MenuSprite::create(Node* nodeNormal, Node* nodeSelected, Node* nodeClicked)
{
	MenuSprite* menuSprite = new MenuSprite(nodeNormal, nodeSelected, nodeClicked);

	menuSprite->autorelease();

	return menuSprite;
}

MenuSprite::MenuSprite(Node* nodeNormal, Node* nodeSelected, Node* nodeClicked)
{
	this->mouseClickEvent = nullptr;
	this->mouseDownEvent = nullptr;
	this->mouseDragEvent = nullptr;
	this->mouseOverEvent = nullptr;
	this->isClickInit = false;
	this->isClicked = false;

	this->clickSound = Resources::Sounds_ButtonClick1;
	this->mouseOverSound = "";

	this->sprite = nodeNormal;
	this->spriteSelected = nodeSelected;
	this->spriteClicked = nodeClicked;

	this->setCascadeOpacityEnabled(true);
	this->spriteClicked->setVisible(false);
	this->spriteSelected->setVisible(false);

	this->setContentSize(this->sprite->getContentSize());

	this->addChild(this->sprite);
	this->addChild(this->spriteClicked);
	this->addChild(this->spriteSelected);

	this->initializeListeners();
	this->scheduleUpdate();
}

MenuSprite::~MenuSprite()
{
}

void MenuSprite::update(float)
{
	this->spriteClicked->setPosition(this->sprite->getPosition());
	this->spriteSelected->setPosition(this->sprite->getPosition());
}

void MenuSprite::setClickCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseClick)
{
	this->mouseClickEvent = onMouseClick;
}

void MenuSprite::setMouseDownCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseDown)
{
	this->mouseDownEvent = onMouseDown;
}

void MenuSprite::setMouseDragCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseDrag)
{
	this->mouseDragEvent = onMouseDrag;
}

void MenuSprite::setMouseOverCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseOver)
{
	this->mouseOverEvent = onMouseOver;
}

void MenuSprite::setMouseOverSound(std::string soundResource)
{
	this->mouseOverSound = soundResource;
}

void MenuSprite::setClickSound(std::string soundResource)
{
	this->clickSound = soundResource;
}

void MenuSprite::initializeListeners()
{
	EventListenerMouse* mouseListener = EventListenerMouse::create();
	EventListenerCustom* customListener = EventListenerCustom::create(Mouse::MouseMoveEvent, CC_CALLBACK_1(MenuSprite::onMouseSpriteMove, this));

	mouseListener->onMouseUp = CC_CALLBACK_1(MenuSprite::onMouseUp, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MenuSprite::onMouseDown, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(customListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

bool MenuSprite::intersects(Vec2 mousePos)
{
	if (dynamic_cast<const LayerColor*>(this->sprite) != nullptr)
	{
		return Utils::intersectsV2(this, Vec2(mousePos.x, mousePos.y));
	}

	return Utils::intersects(this, Vec2(mousePos.x, mousePos.y));
}

void MenuSprite::onMouseSpriteMove(EventCustom* event)
{
	Mouse::MouseEventArgs* args = static_cast<Mouse::MouseEventArgs*>(event->getUserData());

	if (Utils::isVisible(this))
	{
		// Mouse drag callback
		if (args->innerEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		{
			if (this->isClicked && this->mouseDragEvent != nullptr)
			{
				this->mouseDragEvent(this, args->innerEvent);
			}
		}
		else
		{
			this->isClickInit = false;
			this->isClicked = false;
		}

		if (this->intersects(Vec2(args->mouseX, args->mouseY)))
		{
			Mouse::getInstance()->setCanClick(true);

			if (args->innerEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
			{
				// Show mouse click sprite
				this->sprite->setVisible(false);
				this->spriteClicked->setVisible(true);
				this->spriteSelected->setVisible(false);

				// Mouse down callback
				if (this->mouseDownEvent != nullptr)
				{
					this->mouseDownEvent(this, args->innerEvent);
				}
			}
			else
			{
				// Show mouse hover sprite
				this->sprite->setVisible(false);
				this->spriteClicked->setVisible(false);
				this->spriteSelected->setVisible(true);
			}

			// Mouse over callback
			if (this->mouseOverEvent != nullptr)
			{
				this->mouseOverEvent(this, args->innerEvent);
			}
		}
		else
		{
			// Show normal sprite
			this->sprite->setVisible(true);
			this->spriteClicked->setVisible(false);
			this->spriteSelected->setVisible(false);
		}
	}
}

void MenuSprite::onMouseDown(EventMouse* event)
{
	if (Utils::isVisible(this))
	{
		if (this->intersects(Vec2(event->getCursorX(), event->getCursorY())))
		{
			if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
			{
				if (!this->isClickInit)
				{
					this->isClicked = true;
				}
			}
		}

		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		{
			this->isClickInit = true;
		}
	}
}

void MenuSprite::onMouseUp(EventMouse* event)
{
	if (Utils::isVisible(this) && this->intersects(Vec2(event->getCursorX(), event->getCursorY())))
	{
		if (this->mouseClickEvent != nullptr)
		{
			if (this->isClicked)
			{
				// Mouse click callback
				this->mouseClickEvent(this, event);

				// Play click sound
				if (this->clickSound.length() > 0)
				{
					SoundManager::playSoundResource(this->clickSound);
				}

				event->stopPropagation();
			}
		}

		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		{
			this->isClickInit = false;
			this->isClicked = false;
		}
	}
}
