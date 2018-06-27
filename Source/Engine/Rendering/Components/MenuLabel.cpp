#include "MenuLabel.h"

MenuLabel * MenuLabel::create(std::string labelText, std::string fontResource, float fontSize)
{
	MenuLabel* menuLabel = new MenuLabel(labelText, fontResource, fontSize);

	menuLabel->autorelease();

	return menuLabel;
}

MenuLabel::MenuLabel(std::string labelText, std::string fontResource, float fontSize)
{
	this->menuOnMouseClick = nullptr;

	this->label = Label::createWithTTF(labelText, fontResource, fontSize);
	this->labelHighlighted = Label::createWithTTF(labelText, fontResource, fontSize);

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
	Node::onEnter();

	this->initializeListeners();
}

void MenuLabel::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	EventListenerMouse* mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = CC_CALLBACK_1(MenuLabel::onMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MenuLabel::onMouseDown, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
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
