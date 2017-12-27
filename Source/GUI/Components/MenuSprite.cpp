#include "MenuSprite.h"

MenuSprite* MenuSprite::create(std::string spriteResource, std::string spriteSelectedResource, std::string spriteClickedResource)
{
	MenuSprite* menuSprite = new MenuSprite(spriteResource, spriteSelectedResource, spriteClickedResource);

	menuSprite->autorelease();

	return menuSprite;
}

MenuSprite::MenuSprite(std::string spriteResource, std::string spriteSelectedResource, std::string spriteClickedResource)
{
	this->mouseClickEvent = nullptr;
	this->mouseDownEvent = nullptr;
	this->mouseDragEvent = nullptr;
	this->mouseOverEvent = nullptr;
	this->isDragging = false;

	this->clickSound = Resources::Sounds_ButtonClick1;
	this->mouseOverSound = "";

	this->sprite = Sprite::create(spriteResource);
	this->spriteClicked = Sprite::create(spriteClickedResource);
	this->spriteSelected = Sprite::create(spriteSelectedResource);

	this->setCascadeOpacityEnabled(true);
	this->spriteClicked->setVisible(false);
	this->spriteSelected->setVisible(false);

	this->setContentSize(this->sprite->getContentSize());

	this->addChild(this->sprite);
	this->addChild(this->spriteClicked);
	this->addChild(this->spriteSelected);

	this->initializeListeners();
}

MenuSprite::~MenuSprite()
{
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
	EventListenerCustom* customListener = EventListenerCustom::create(Mouse::getInstance()->MouseMoveEvent, CC_CALLBACK_1(MenuSprite::onMouseSpriteMove, this));

	mouseListener->onMouseUp = CC_CALLBACK_1(MenuSprite::onMouseUp, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MenuSprite::onMouseDown, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(customListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void MenuSprite::onMouseSpriteMove(EventCustom* event)
{
	Mouse::MouseEventArgs* args = static_cast<Mouse::MouseEventArgs*>(event->getUserData());

	if (this->isVisible())
	{
		// Mouse drag callback
		if (args->innerEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		{
			if (this->isDragging && this->mouseDragEvent != nullptr)
			{
				this->mouseDragEvent(this, args->innerEvent);
			}
		}

		if (Utils::intersects(this, Vec2(args->mouseX, args->mouseY)))
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
	if (this->mouseDragEvent != nullptr && this->isVisible())
	{
		if (Utils::intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
		{
			if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
			{
				this->isDragging = true;
			}
		}
	}
}

void MenuSprite::onMouseUp(EventMouse* event)
{
	if (this->mouseDragEvent != nullptr && this->isVisible())
	{
		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		{
			this->isDragging = false;
		}
	}

	if (this->mouseClickEvent != nullptr && this->isVisible())
	{
		if (Utils::intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
		{
			// Mouse click callback
			this->mouseClickEvent(this, event);

			// Play click sound
			if (this->clickSound.length() > 0)
			{
				SoundManager::getInstance()->playSoundResource(this->clickSound);
			}

			event->stopPropagation();
		}
	}
}