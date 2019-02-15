#include "ClickableNode.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Input/Input.h"
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

ClickableNode* ClickableNode::create()
{
	return ClickableNode::create(Node::create(), Node::create());
}

ClickableNode* ClickableNode::create(std::string spriteNormal, std::string spriteSelectedResource)
{
	return ClickableNode::create(Sprite::create(spriteNormal), Sprite::create(spriteSelectedResource));
}

ClickableNode* ClickableNode::create(Node* nodeNormal, Node* nodeSelected)
{
	ClickableNode* instance = new ClickableNode(nodeNormal, nodeSelected);

	instance->autorelease();

	return instance;
}

ClickableNode::ClickableNode(Node* nodeNormal, Node* nodeSelected)
{
	this->mouseClickEvent = nullptr;
	this->mouseDownEvent = nullptr;
	this->mouseDragEvent = nullptr;
	this->mouseOverEvent = nullptr;
	this->mouseScrollEvent = nullptr;
	this->interactionEnabled = true;
	this->isClickInit = false;
	this->isClicked = false;
	this->isMousedOver = false;
	this->modifier = EventKeyboard::KeyCode::KEY_NONE;
	this->debugHitbox = DrawNode::create();

	this->clickSound = "";
	this->mouseOverSound = SoundResources::ButtonRollover1;

	this->sprite = nodeNormal;
	this->spriteSelected = nodeSelected;

	this->debugHitbox->setVisible(false);

	this->debugCachedPos = Vec2::ZERO;
	this->setContentSize(this->sprite->getContentSize());

	this->addChild(this->sprite);
	this->addChild(this->spriteSelected);
	this->addChild(this->debugHitbox);
}

ClickableNode::~ClickableNode()
{
}

void ClickableNode::onEnter()
{
	super::onEnter();

	this->isClickInit = false;
	this->isClicked = false;

	this->sprite->setVisible(true);
	this->spriteSelected->setVisible(false);

	this->scheduleUpdate();
}

void ClickableNode::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	// Trigger mouse move event to refresh cursor state
	MouseEvents::MouseEventArgs args = MouseState::getMouseState();
	this->mouseMove(&args);
}

void ClickableNode::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* mouseMoveListener = EventListenerCustom::create(MouseEvents::MouseMoveEvent, [=](EventCustom* eventCustom)
	{
		this->mouseMove(static_cast<MouseEvents::MouseEventArgs*>(eventCustom->getUserData()), eventCustom);
	});

	EventListenerCustom* mouseRefreshListener = EventListenerCustom::create(MouseEvents::MouseRefreshEvent, [=](EventCustom* eventCustom)
	{
		this->mouseMove(static_cast<MouseEvents::MouseEventArgs*>(eventCustom->getUserData()), eventCustom, true);
	});

	EventListenerCustom* mouseDownListener = EventListenerCustom::create(MouseEvents::MouseDownEvent, [=](EventCustom* eventCustom)
	{
		this->mouseDown(static_cast<MouseEvents::MouseEventArgs*>(eventCustom->getUserData()), eventCustom);
	});

	EventListenerCustom* mouseUpListener = EventListenerCustom::create(MouseEvents::MouseUpEvent, [=](EventCustom* eventCustom)
	{
		this->mouseUp(static_cast<MouseEvents::MouseEventArgs*>(eventCustom->getUserData()), eventCustom);
	});

	EventListenerCustom* mouseScrollListener = EventListenerCustom::create(MouseEvents::MouseScrollEvent, [=](EventCustom* eventCustom)
	{
		this->mouseScroll(static_cast<MouseEvents::MouseEventArgs*>(eventCustom->getUserData()), eventCustom);
	});

	this->addEventListener(mouseMoveListener);
	this->addEventListener(mouseRefreshListener);
	this->addEventListener(mouseDownListener);
	this->addEventListener(mouseUpListener);
	this->addEventListener(mouseScrollListener);
}

void ClickableNode::update(float dt)
{
	super::update(dt);

	// Update the selected sprite to track the main sprite
	this->spriteSelected->setPosition(this->sprite->getPosition());
}

void ClickableNode::setDebugDrawPosition()
{
	this->debugHitbox->setPosition(-Vec2(this->getContentSize() / 2.0f));
}

void ClickableNode::setContentSize(const Size & size)
{
	super::setContentSize(size);

	this->debugHitbox->clear();
	this->debugHitbox->drawRect(Vec2::ZERO, Vec2(size), Color4F(1.0f, 1.0f, 0.0f, 0.35f));
	this->debugHitbox->setContentSize(size);

	this->setDebugDrawPosition();
}

void ClickableNode::onDeveloperModeEnable()
{
	super::onDeveloperModeEnable();

	this->debugHitbox->setVisible(true);
}

void ClickableNode::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	this->debugHitbox->setVisible(false);
}

void ClickableNode::disableInteraction(GLubyte newOpacity)
{
	this->interactionEnabled = false;
	this->showSprite(this->sprite);
	this->setOpacity(newOpacity);
}

void ClickableNode::enableInteraction(GLubyte newOpacity)
{
	this->interactionEnabled = true;
	this->showSprite(this->sprite);
	this->setOpacity(newOpacity);
}

void ClickableNode::setClickModifier(EventKeyboard::KeyCode modifier)
{
	this->modifier = modifier;
}

void ClickableNode::setClickCallback(std::function<void(ClickableNode*, MouseEvents::MouseEventArgs* args)> onMouseClick)
{
	this->mouseClickEvent = onMouseClick;
}

void ClickableNode::setMouseDownCallback(std::function<void(ClickableNode*, MouseEvents::MouseEventArgs* args)> onMouseDown)
{
	this->mouseDownEvent = onMouseDown;
}

void ClickableNode::setMouseDragCallback(std::function<void(ClickableNode*, MouseEvents::MouseEventArgs* args)> onMouseDrag)
{
	this->mouseDragEvent = onMouseDrag;
}

void ClickableNode::setMouseOverCallback(std::function<void(ClickableNode*, MouseEvents::MouseEventArgs* args)> onMouseOver)
{
	this->mouseOverEvent = onMouseOver;
}

void ClickableNode::setMouseOutCallback(std::function<void(ClickableNode*, MouseEvents::MouseEventArgs* args)> onMouseOut)
{
	this->mouseOutEvent = onMouseOut;
}

void ClickableNode::setMouseScrollCallback(std::function<void(ClickableNode*, MouseEvents::MouseEventArgs* args)> onScroll)
{
	this->mouseScrollEvent = onScroll;
}

void ClickableNode::setMouseOverSound(std::string soundResource)
{
	this->mouseOverSound = soundResource;
}

void ClickableNode::setClickSound(std::string soundResource)
{
	this->clickSound = soundResource;
}

void ClickableNode::showSprite(Node* sprite)
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

void ClickableNode::clearState()
{
	this->isClicked = false;
	this->isClickInit = false;
}

void ClickableNode::mouseMove(MouseEvents::MouseEventArgs* args, EventCustom* event, bool isRefresh)
{
	if (!this->interactionEnabled || (this->modifier != Input::getActiveModifiers()) || !GameUtils::isVisible(this))
	{
		return;
	}

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
		this->clearState();
	}

	if (!args->handled && GameUtils::intersects(this, Vec2(args->mouseCoords)))
	{
		MouseEvents::TriggerClickableMouseOverEvent();

		this->isMousedOver = true;

		if (this->mouseDownEvent != nullptr || this->mouseClickEvent != nullptr || this->mouseDragEvent != nullptr)
		{
			// Play mouse over sound
			if (!args->isDragging && !isRefresh && this->currentSprite != this->spriteSelected)
			{
				if (!this->mouseOverSound.empty())
				{
					SoundManager::playSoundResource(this->mouseOverSound);
				}
			}

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

void ClickableNode::mouseDown(MouseEvents::MouseEventArgs* args, EventCustom* event)
{
	if (!this->interactionEnabled || (this->modifier != Input::getActiveModifiers()) || !GameUtils::isVisible(this))
	{
		return;
	}

	if (GameUtils::intersects(this, Vec2(args->mouseCoords)) && args->isLeftClicked)
	{
		if (this->mouseDownEvent != nullptr)
		{
			// Mouse down callback
			this->mouseDownEvent(this, args);
		}

		if (!this->isClickInit)
		{
			if (this->mouseDragEvent != nullptr)
			{
				MouseEvents::TriggerDragEvent();
			}

			this->isClicked = true;
		}
	}

	if (args->isLeftClicked)
	{
		this->isClickInit = true;
	}
}

void ClickableNode::mouseUp(MouseEvents::MouseEventArgs* args, EventCustom* event)
{
	if (!this->interactionEnabled || (this->modifier != Input::getActiveModifiers()) || !GameUtils::isVisible(this))
	{
		return;
	}

	this->isClickInit = false;

	if (GameUtils::intersects(this, Vec2(args->mouseCoords)) && this->mouseClickEvent != nullptr && !args->isDragging && this->isClicked)
	{
		this->isClicked = false;

		// Play click sound
		if (!this->clickSound.empty())
		{
			SoundManager::playSoundResource(this->clickSound);
		}

		this->showSprite(this->spriteSelected);

		if (event != nullptr)
		{
			event->stopPropagation();
		}

		// Mouse click callback. IMPORTANT: Do not access any references to 'this' from here to the end of the function, in the case where this object is deleted in a callback
		this->mouseClickEvent(this, args);
	}
	else
	{
		this->isClicked = false;
	}
}

void ClickableNode::mouseScroll(MouseEvents::MouseEventArgs* args, EventCustom* event)
{
	if (!this->interactionEnabled || !GameUtils::isVisible(this))
	{
		return;
	}

	if (this->mouseScrollEvent != nullptr && GameUtils::intersects(this, Vec2(args->mouseCoords)))
	{
		this->mouseScrollEvent(this, args);
	}
}
