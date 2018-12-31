#include "MenuSprite.h"

#include <typeinfo>

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/MouseState.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

/*
NOTE TO OTHER DEVELOPERS:

This is the worst written class in this entire codebase. If you need to change something here, probably just ask Zac.

One day I'll figure out how to refactor this sphagetti garbage fire of state variables.
*/

MenuSprite* MenuSprite::create(std::string spriteNormal, std::string spriteSelectedResource)
{
	return MenuSprite::create(Sprite::create(spriteNormal), Sprite::create(spriteSelectedResource));
}

MenuSprite* MenuSprite::create(Node* nodeNormal, Node* nodeSelected)
{
	MenuSprite* instance = new MenuSprite(nodeNormal, nodeSelected);

	instance->autorelease();

	return instance;
}

MenuSprite::MenuSprite(Node* nodeNormal, Node* nodeSelected)
{
	this->mouseClickEvent = nullptr;
	this->mouseDownEvent = nullptr;
	this->mouseDragEvent = nullptr;
	this->mouseOverEvent = nullptr;
	this->interactionEnabled = true;
	this->isClickInit = false;
	this->isClicked = false;
	this->isMousedOver = false;

	this->clickSound = "";
	this->mouseOverSound = SoundResources::ButtonRollover1;

	this->sprite = nodeNormal;
	this->spriteSelected = nodeSelected;

	this->offsetCorrection = Vec2::ZERO;

	this->setContentSize(this->sprite->getContentSize());

	this->addChild(this->sprite);
	this->addChild(this->spriteSelected);
}

MenuSprite::~MenuSprite()
{
}

void MenuSprite::onEnter()
{
	super::onEnter();

	this->isClickInit = false;
	this->isClicked = false;

	this->sprite->setVisible(true);
	this->spriteSelected->setVisible(false);

	this->scheduleUpdate();
}

void MenuSprite::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	// Trigger mouse move event to refresh cursor state
	MouseEvents::MouseEventArgs args = MouseState::getMouseState();
	this->mouseMove(&args);
}

void MenuSprite::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* mouseMoveListener = EventListenerCustom::create(MouseEvents::MouseMoveEvent, CC_CALLBACK_1(MenuSprite::onMouseMove, this));
	EventListenerCustom* mouseRefreshListener = EventListenerCustom::create(MouseEvents::MouseRefreshEvent, CC_CALLBACK_1(MenuSprite::onMouseRefresh, this));
	EventListenerCustom* mouseDownListener = EventListenerCustom::create(MouseEvents::MouseDownEvent, CC_CALLBACK_1(MenuSprite::onMouseDown, this));
	EventListenerCustom* mouseUpListener = EventListenerCustom::create(MouseEvents::MouseUpEvent, CC_CALLBACK_1(MenuSprite::onMouseUp, this));

	this->addEventListener(mouseMoveListener);
	this->addEventListener(mouseRefreshListener);
	this->addEventListener(mouseDownListener);
	this->addEventListener(mouseUpListener);
}

void MenuSprite::update(float dt)
{
	super::update(dt);

	// Update the selected sprite to track the main sprite
	this->spriteSelected->setPosition(this->sprite->getPosition());
}

void MenuSprite::disableInteraction(GLubyte newOpacity)
{
	this->interactionEnabled = false;
	this->showSprite(this->sprite);
	this->setOpacity(newOpacity);
}

void MenuSprite::enableInteraction(GLubyte newOpacity)
{
	this->interactionEnabled = true;
	this->showSprite(this->sprite);
	this->setOpacity(newOpacity);
}

void MenuSprite::setContentScale(float scale)
{
	this->setContentSize(this->sprite->getContentSize() * scale);
}

void MenuSprite::setOffsetCorrection(Vec2 newOffsetCorrection)
{
	this->offsetCorrection = newOffsetCorrection;
}

void MenuSprite::setClickCallback(std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> onMouseClick)
{
	this->mouseClickEvent = onMouseClick;
}

void MenuSprite::setMouseDownCallback(std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> onMouseDown)
{
	this->mouseDownEvent = onMouseDown;
}

void MenuSprite::setMouseDragCallback(std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> onMouseDrag)
{
	this->mouseDragEvent = onMouseDrag;
}

void MenuSprite::setMouseOverCallback(std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> onMouseOver)
{
	this->mouseOverEvent = onMouseOver;
}

void MenuSprite::setMouseOutCallback(std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> onMouseOut)
{
	this->mouseOutEvent = onMouseOut;
}

void MenuSprite::setMouseOverSound(std::string soundResource)
{
	this->mouseOverSound = soundResource;
}

void MenuSprite::setClickSound(std::string soundResource)
{
	this->clickSound = soundResource;
}

bool MenuSprite::intersects(Vec2 mousePos)
{
	if (dynamic_cast<const LayerColor*>(this->sprite) != nullptr)
	{
		return GameUtils::intersectsV2(this, Vec2(mousePos.x, mousePos.y) + this->offsetCorrection);
	}

	return GameUtils::intersects(this, Vec2(mousePos.x, mousePos.y) + this->offsetCorrection);
}

void MenuSprite::showSprite(Node* sprite)
{
	// Hide everything
	this->sprite->setVisible(false);
	this->spriteSelected->setVisible(false);

	if (this->interactionEnabled)
	{
		// Show the specified one
		sprite->setVisible(true);
	}
	else
	{
		// Interaction disabled -- only show the main sprite
		this->sprite->setVisible(true);
	}

	this->currentSprite = sprite;
}

void MenuSprite::onMouseMove(EventCustom* event)
{
	this->mouseMove(static_cast<MouseEvents::MouseEventArgs*>(event->getUserData()), event);
}

void MenuSprite::onMouseRefresh(EventCustom* event)
{
	this->mouseMove(static_cast<MouseEvents::MouseEventArgs*>(event->getUserData()), event, true);
}

void MenuSprite::onMouseDown(EventCustom* event)
{
	this->mouseDown(static_cast<MouseEvents::MouseEventArgs*>(event->getUserData()), event);
}

void MenuSprite::onMouseUp(EventCustom* event)
{
	this->mouseUp(static_cast<MouseEvents::MouseEventArgs*>(event->getUserData()), event);
}

void MenuSprite::mouseMove(MouseEvents::MouseEventArgs* args, EventCustom* event, bool isRefresh)
{
	if (!this->interactionEnabled)
	{
		return;
	}

	if (GameUtils::isVisible(this))
	{
		// Mouse drag callback
		if (args->isLeftClicked)
		{
			if (this->isClicked && this->mouseDragEvent != nullptr)
			{
				MouseEvents::TriggerDragEvent();
				this->mouseDragEvent(this, args);
			}
		}
		else
		{
			this->isClickInit = false;
			this->isClicked = false;
		}

		if (!args->handled && this->intersects(args->mouseCoords))
		{
			MouseEvents::TriggerClickableMouseOverEvent();

			this->isMousedOver = true;

			// Play mouse over sound
			if (!args->isDragging && !isRefresh && this->currentSprite != this->spriteSelected)
			{
				if (this->mouseOverSound.length() > 0)
				{
					SoundManager::playSoundResource(this->mouseOverSound);
				}
			}

			if (!args->isDragging && args->isLeftClicked)
			{
				// Mouse down callback
				if (this->mouseDownEvent != nullptr)
				{
					this->mouseDownEvent(this, args);
				}
			}
			else
			{
				this->showSprite(this->spriteSelected);
			}

			// Mouse over callback
			if (this->mouseOverEvent != nullptr)
			{
				this->mouseOverEvent(this, args);
			}

			// For the use cases of this game, I see no case in which we want to mouse over two things at once
			// If this changes, we will have to make this line optional/configurable
			args->handled = true;
		}
		else
		{
			// Mouse out event
			if (this->isMousedOver && this->mouseOutEvent != nullptr)
			{
				this->mouseOutEvent(this, args);
			}

			this->isMousedOver = false;

			this->showSprite(this->sprite);
		}
	}
}

void MenuSprite::mouseDown(MouseEvents::MouseEventArgs* args, EventCustom* event)
{
	if (!this->interactionEnabled)
	{
		return;
	}

	if (GameUtils::isVisible(this))
	{
		if (this->intersects(args->mouseCoords))
		{
			if (args->isLeftClicked)
			{
				if (!this->isClickInit)
				{
					if (this->mouseDragEvent != nullptr)
					{
						MouseEvents::TriggerDragEvent();
					}

					this->isClicked = true;
				}

			}
		}

		if (args->isLeftClicked)
		{
			this->isClickInit = true;
		}
	}
}

void MenuSprite::mouseUp(MouseEvents::MouseEventArgs* args, EventCustom* event)
{
	if (!this->interactionEnabled)
	{
		return;
	}

	if (GameUtils::isVisible(this) && this->intersects(args->mouseCoords))
	{
		if (this->mouseClickEvent != nullptr)
		{
			if (!args->isDragging && this->isClicked)
			{
				// Mouse click callback
				this->mouseClickEvent(this, args);

				// Play click sound
				if (this->clickSound.length() > 0)
				{
					SoundManager::playSoundResource(this->clickSound);
				}

				this->showSprite(this->spriteSelected);

				if (event != nullptr)
				{
					event->stopPropagation();
				}
			}
		}
	}

	this->isClickInit = false;
	this->isClicked = false;
}
