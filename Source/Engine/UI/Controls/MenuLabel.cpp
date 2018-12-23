#include "MenuLabel.h"

#include "cocos/2d/CCLabel.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListenerMouse.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

MenuLabel* MenuLabel::create(LocalizedLabel* label)
{
	MenuLabel* instance = new MenuLabel(label);

	instance->autorelease();

	return instance;
}

MenuLabel::MenuLabel(LocalizedLabel* label)
{
	this->menuOnMouseClick = nullptr;

	this->label = label;
	this->labelHighlighted = label->clone();

	this->label->enableOutline(Color4B::BLACK, fontOutlineSize);

	this->addChild(this->labelHighlighted);
	this->addChild(this->label);

	this->setContentSize(this->label->getContentSize());
}

MenuLabel::~MenuLabel()
{
}

void MenuLabel::setColor(Color4B color)
{
	this->normalColor = color;

	this->label->setTextColor(color);
	this->labelHighlighted->setTextColor(color);
}

void MenuLabel::setHoverColor(Color4B color)
{
	this->hoverColor = color;
}

void MenuLabel::setGlowColor(Color4B color)
{
	this->glowColor = color;
}

void MenuLabel::setCallback(std::function<void(MenuLabel*)> callback)
{
	this->menuOnMouseClick = callback;
}

void MenuLabel::setText(std::string text)
{
	this->label->setString(text);
	this->labelHighlighted->setString(text);

	this->setContentSize(this->label->getContentSize());
}

void MenuLabel::onEnter()
{
	SmartNode::onEnter();
}

void MenuLabel::initializeListeners()
{
	SmartNode::initializeListeners();

	this->getEventDispatcher()->removeEventListenersForTarget(this);

	EventListenerMouse* mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = CC_CALLBACK_1(MenuLabel::onMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MenuLabel::onMouseDown, this);

	this->addEventListener(mouseListener);
}

void MenuLabel::onMouseMove(EventMouse* event)
{
	if (this->menuOnMouseClick != nullptr && this->isVisible())
	{
		if (GameUtils::intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
		{
			this->label->setTextColor(this->hoverColor);
			this->labelHighlighted->setTextColor(this->hoverColor);

			this->labelHighlighted->enableOutline(this->glowColor, highlightOutlineSize);
		}
		else
		{
			this->label->setTextColor(this->normalColor);
			this->labelHighlighted->setTextColor(this->normalColor);

			this->labelHighlighted->enableOutline(Color4B::BLACK, 1);
		}
	}
}

void MenuLabel::onMouseDown(EventMouse* event)
{
	if (this->menuOnMouseClick != nullptr && this->isVisible())
	{
		if (GameUtils::intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
		{
			this->menuOnMouseClick(this);
		}
	}
}
