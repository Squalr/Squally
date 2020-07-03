#include "ClickableNode.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Input/Input.h"
#include "Engine/Input/MouseState.h"
#include "Engine/Sound/Sound.h"
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

ClickableNode* ClickableNode::create(std::string spriteResource, std::string spriteSelectedResource)
{
	return ClickableNode::create(Sprite::create(spriteResource), Sprite::create(spriteSelectedResource));
}

ClickableNode* ClickableNode::create(Node* content, Node* contentSelected)
{
	ClickableNode* instance = new ClickableNode(content, contentSelected);

	instance->autorelease();

	return instance;
}

ClickableNode::ClickableNode(Node* content, Node* contentSelected)
{
	this->mouseClickEvent = nullptr;
	this->mouseInEvent = nullptr;
	this->mouseDownEvent = nullptr;
	this->mouseDragEvent = nullptr;
	this->mouseOverEvent = nullptr;
	this->mousePressEvent = nullptr;
	this->mouseReleaseNoHitTestEvent = nullptr;
	this->mouseReleaseEvent = nullptr;
	this->mouseScrollEvent = nullptr;
	this->allowCollisionWhenInvisible = false;
	this->interactionEnabled = true;
	this->wasAnywhereClicked = false;
	this->wasClickedDirectly = false;
	this->allowMouseOutDeselection = true;
	this->isMousedOver = false;
	this->modifierReleasedListener = nullptr;
	this->modifier = EventKeyboard::KeyCode::KEY_NONE;
	this->intersectFunction = nullptr;

	if (DeveloperModeController::IsDeveloperBuild)
	{
		this->debugHitbox = DrawNode::create();
		this->debugHitbox->setVisible(false);
	}
	else
	{
		this->debugHitbox = nullptr;
	}

	this->clickSound = Sound::create();
	this->mouseOverSound = Sound::create(SoundResources::Menus_ButtonRollover1);

	this->content = content;
	this->contentSelected = contentSelected;

	this->debugCachedPos = Vec2::ZERO;
	this->setContentSize(this->content == nullptr ? Size(256.0f, 128.0f) : this->content->getContentSize());

	this->addChild(this->content);
	this->addChild(this->contentSelected);

	if (this->debugHitbox != nullptr)
	{
		this->addChild(this->debugHitbox);
	}

	this->addChild(this->clickSound);
	this->addChild(this->mouseOverSound);
}

ClickableNode::~ClickableNode()
{
}

void ClickableNode::onEnter()
{
	super::onEnter();

	this->wasAnywhereClicked = false;
	this->wasClickedDirectly = false;

	this->content->setVisible(true);
	this->contentSelected->setVisible(false);
}

void ClickableNode::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	// Trigger mouse move event to refresh cursor state
	InputEvents::MouseEventArgs args = MouseState::getMouseState();
	this->mouseMove(&args);
}

void ClickableNode::initializeListeners()
{
	super::initializeListeners();

	this->addEventListener(EventListenerCustom::create(InputEvents::EventMouseMove, [=](EventCustom* eventCustom)
	{
		this->mouseMove(static_cast<InputEvents::MouseEventArgs*>(eventCustom->getUserData()), eventCustom);
	}));

	this->addEventListener(EventListenerCustom::create(InputEvents::EventMouseRefresh, [=](EventCustom* eventCustom)
	{
		this->mouseMove(static_cast<InputEvents::MouseEventArgs*>(eventCustom->getUserData()), eventCustom, true);
	}));

	this->addEventListener(EventListenerCustom::create(InputEvents::EventMouseDown, [=](EventCustom* eventCustom)
	{
		this->mouseDown(static_cast<InputEvents::MouseEventArgs*>(eventCustom->getUserData()), eventCustom);
	}));

	this->addEventListener(EventListenerCustom::create(InputEvents::EventMouseUp, [=](EventCustom* eventCustom)
	{
		this->mouseUp(static_cast<InputEvents::MouseEventArgs*>(eventCustom->getUserData()), eventCustom);
	}));

	this->addEventListener(EventListenerCustom::create(InputEvents::EventMouseScroll, [=](EventCustom* eventCustom)
	{
		this->mouseScroll(static_cast<InputEvents::MouseEventArgs*>(eventCustom->getUserData()), eventCustom);
	}));
}

void ClickableNode::setDebugDrawPosition()
{
	if (this->debugHitbox != nullptr)
	{
		this->debugHitbox->setPosition(-Vec2(this->getContentSize() / 2.0f));
	}
}

bool ClickableNode::canInteract()
{
	return this->mouseClickEvent != nullptr && (this->interactionEnabled && (this->allowCollisionWhenInvisible || GameUtils::isVisible(this)));
}

void ClickableNode::interact()
{
	if (this->canInteract())
	{
		this->mouseClickEvent(nullptr);
	}
}

void ClickableNode::setContentSize(const Size & size)
{
	super::setContentSize(size);

	if (this->debugHitbox != nullptr)
	{
		this->debugHitbox->clear();
		this->debugHitbox->drawRect(Vec2::ZERO, Vec2(size), Color4F(1.0f, 1.0f, 0.0f, 0.35f));
		this->debugHitbox->setContentSize(size);

		this->setDebugDrawPosition();
	}
}

void ClickableNode::onDeveloperModeEnable(int debugLevel)
{
	super::onDeveloperModeEnable(debugLevel);

	if (this->debugHitbox != nullptr)
	{
		this->debugHitbox->setVisible(true);
	}
}

void ClickableNode::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	if (this->debugHitbox != nullptr)
	{
		this->debugHitbox->setVisible(false);
	}
}

void ClickableNode::setAllowCollisionWhenInvisible(bool allowCollisionWhenInvisible)
{
	this->allowCollisionWhenInvisible = allowCollisionWhenInvisible;
}

void ClickableNode::disableInteraction(GLubyte newOpacity)
{
	this->interactionEnabled = false;
	this->showContent(this->content);
	this->setOpacity(newOpacity);

	// Refresh the mouse state in case the mouse was already hovered over this in order to keep the mouse sprite valid
	// InputEvents::TriggerMouseRefresh(MouseState::getMouseState());
}

void ClickableNode::enableInteraction(GLubyte newOpacity)
{
	this->interactionEnabled = true;
	this->showContent(this->content);
	this->setOpacity(newOpacity);

	// Refresh the mouse state in case the mouse was already hovered over this in order to keep the mouse sprite valid
	// InputEvents::TriggerMouseRefresh(MouseState::getMouseState());
}

void ClickableNode::setClickModifier(EventKeyboard::KeyCode modifier)
{
	if (this->modifierReleasedListener != nullptr)
	{
		this->removeEventListener(this->modifierReleasedListener);
	}
	
	this->modifier = modifier;

	this->modifierReleasedListener = this->whenKeyReleased({ modifier }, [=](InputEvents::InputArgs*)
	{
		InputEvents::MouseEventArgs args = MouseState::getMouseState();

		this->mouseOut(&args, true);
	}, false);
}

void ClickableNode::setMouseClickCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMouseClick)
{
	this->mouseClickEvent = onMouseClick;
}

void ClickableNode::setMouseInCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMouseIn)
{
	this->mouseInEvent = onMouseIn;
}

void ClickableNode::setMouseDownCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMouseDown)
{
	this->mouseDownEvent = onMouseDown;
}

void ClickableNode::setMousePressCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMousePressEvent)
{
	this->mousePressEvent = onMousePressEvent;
}

void ClickableNode::setMouseReleaseNoHitTestCallback(std::function<void(InputEvents::MouseEventArgs* args)> mouseReleaseNoHitTestEvent)
{
	this->mouseReleaseNoHitTestEvent = mouseReleaseNoHitTestEvent;
}

void ClickableNode::setMouseReleaseCallback(std::function<void(InputEvents::MouseEventArgs* args)> mouseReleaseEvent)
{
	this->mouseReleaseEvent = mouseReleaseEvent;
}

void ClickableNode::setMouseDragCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMouseDrag)
{
	this->mouseDragEvent = onMouseDrag;
}

void ClickableNode::setMouseOverCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMouseOver)
{
	this->mouseOverEvent = onMouseOver;
}

void ClickableNode::setMouseOutCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMouseOut)
{
	this->mouseOutEvent = onMouseOut;
}

void ClickableNode::setMouseScrollCallback(std::function<void(InputEvents::MouseEventArgs* args)> onScroll)
{
	this->mouseScrollEvent = onScroll;
}

void ClickableNode::setMouseOverSound(std::string soundResource)
{
	this->mouseOverSound->setSoundResource(soundResource);
}

void ClickableNode::setClickSound(std::string soundResource)
{
	this->clickSound->setSoundResource(soundResource);
}

void ClickableNode::showContent(Node* sprite)
{
	// Hide everything
	if (this->content != nullptr)
	{
		this->content->setVisible(false);
	}

	if (this->contentSelected != nullptr)
	{
		this->contentSelected->setVisible(false);
	}

	if (sprite != nullptr)
	{
		if (this->interactionEnabled)
		{
			// Show the specified one
			sprite->setVisible(true);
		}
		else
		{
			// Interaction disabled -- only show the main sprite
			this->content->setVisible(true);
		}
	}

	this->currentSprite = sprite;
}

void ClickableNode::clearState()
{
	this->wasClickedDirectly = false;
	this->wasAnywhereClicked = false;
}

void ClickableNode::mouseMove(InputEvents::MouseEventArgs* args, EventCustom* event, bool isRefresh)
{
	if (!this->interactionEnabled ||
		(this->modifier != EventKeyboard::KeyCode::KEY_NONE && this->modifier != Input::getActiveModifiers()) ||
		(!this->allowCollisionWhenInvisible && !GameUtils::isVisible(this)))
	{
		return;
	}

	// Mouse drag callback
	if (args->isLeftClicked)
	{
		if (this->wasClickedDirectly && this->mouseDragEvent != nullptr)
		{
			InputEvents::TriggerDragEvent();
			this->mouseDragEvent(args);
		}
	}
	else
	{
		this->clearState();
	}

	if (!args->isHandled() && this->intersects(args->mouseCoords))
	{
		if (this->mouseDownEvent != nullptr || this->mouseClickEvent != nullptr || this->mouseDragEvent != nullptr)
		{
			InputEvents::TriggerEventClickableMouseOver();
		}

		if (!this->isMousedOver && this->mouseInEvent != nullptr)
		{
			this->mouseInEvent(args);
		}

		this->isMousedOver = true;

		if (this->mouseDownEvent != nullptr || this->mouseClickEvent != nullptr || this->mouseDragEvent != nullptr)
		{
			// Play mouse over sound
			if (!args->isDragging && !isRefresh && this->currentSprite != this->contentSelected)
			{
				this->mouseOverSound->play();
			}

			this->showContent(this->contentSelected);

			// Set args as handled. Caller must un-handle in the callback if they choose.
			args->handle();
		}

		// Mouse over callback
		if (this->mouseOverEvent != nullptr)
		{
			this->mouseOverEvent(args);
		}
	}
	else
	{
		this->mouseOut(args);
	}
}

void ClickableNode::mouseDown(InputEvents::MouseEventArgs* args, EventCustom* event)
{
	if (!this->interactionEnabled || (this->modifier != Input::getActiveModifiers()) || (!this->allowCollisionWhenInvisible && !GameUtils::isVisible(this)))
	{
		return;
	}

	if (this->mouseDownEvent != nullptr || this->mouseClickEvent != nullptr || this->mouseDragEvent != nullptr)
	{
		if (!args->isHandled() && this->intersects(args->mouseCoords) && args->isLeftClicked)
		{
			if (this->mouseDownEvent != nullptr)
			{
				// Mouse down callback
				this->mouseDownEvent(args);
			}

			if (!this->wasAnywhereClicked)
			{
				// Set args as handled. Caller must un-handle in either callback if they choose.
				args->handle();

				if (this->mousePressEvent != nullptr)
				{
					this->mousePressEvent(args);
				}

				if (this->mouseDragEvent != nullptr)
				{
					InputEvents::TriggerDragEvent();
				}

				this->wasClickedDirectly = true;
			}
		}
	}

	if (args->isLeftClicked)
	{
		this->wasAnywhereClicked = true;
	}
}

void ClickableNode::mouseUp(InputEvents::MouseEventArgs* args, EventCustom* event)
{
	if (!this->interactionEnabled || (this->modifier != Input::getActiveModifiers()) || (!this->allowCollisionWhenInvisible && !GameUtils::isVisible(this)))
	{
		return;
	}

	// This event is called despite any arg handled flags
	if (this->wasClickedDirectly && this->mouseReleaseNoHitTestEvent != nullptr)
	{
		this->mouseReleaseNoHitTestEvent(args);
	}

	if (!args->isHandled() && this->intersects(args->mouseCoords) && this->mouseClickEvent != nullptr && !args->isDragging && this->wasClickedDirectly)
	{
		this->wasClickedDirectly = false;
		this->wasAnywhereClicked = false;

		if (this->mouseReleaseEvent != nullptr)
		{
			this->mouseReleaseEvent(args);
		}

		this->clickSound->play();

		this->showContent(this->contentSelected);

		if (event != nullptr)
		{
			event->stopPropagation();
		}

		// Set args as handled. Caller must un-handle in the callback if they choose.
		args->handle();

		// Mouse click callback. IMPORTANT: Do not access any references to 'this' from here to the end of the function, in the case where this object is deleted in a callback
		this->mouseClickEvent(args);
	}
	else
	{
		this->wasClickedDirectly = false;
		this->wasAnywhereClicked = false;
	}
}

void ClickableNode::mouseScroll(InputEvents::MouseEventArgs* args, EventCustom* event)
{
	if (!this->interactionEnabled || !GameUtils::isVisible(this))
	{
		return;
	}

	if (!args->isHandled() && this->mouseScrollEvent != nullptr && this->intersects(args->mouseCoords))
	{
		// Set args as handled. Caller must un-handle in the callback if they choose.
		args->handle();

		this->mouseScrollEvent(args);
	}
}

void ClickableNode::mouseOut(InputEvents::MouseEventArgs* args, bool force)
{
	// Mouse out event
	if ((this->isMousedOver || force) && this->mouseOutEvent != nullptr)
	{
		this->mouseOutEvent(args);
	}

	this->isMousedOver = false;

	if (this->allowMouseOutDeselection)
	{
		this->showContent(this->content);
	}
}

void ClickableNode::toggleAllowMouseOutDeselection(bool allowMouseOutDeselection)
{
	this->allowMouseOutDeselection = allowMouseOutDeselection;
}

void ClickableNode::select()
{
	this->showContent(this->contentSelected);
}

void ClickableNode::deselect()
{
	this->showContent(this->content);
}

bool ClickableNode::isSelected()
{
	return this->currentSprite == this->contentSelected;
}

cocos2d::Node* ClickableNode::getContent()
{
	return this->content;
}

cocos2d::Node* ClickableNode::getContentSelected()
{
	return this->contentSelected;
}

void ClickableNode::setIntersectFunction(std::function<bool(cocos2d::Vec2 mousePos)> intersectFunction)
{
	this->intersectFunction = intersectFunction;
}

bool ClickableNode::intersects(cocos2d::Vec2 mousePos)
{
	if (this->intersectFunction != nullptr)
	{
		return this->intersectFunction(mousePos);
	}

	return GameUtils::intersects(this, mousePos);
}
