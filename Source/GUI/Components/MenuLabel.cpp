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

	this->setCascadeOpacityEnabled(true);

	this->addChild(this->labelHighlighted);
	this->addChild(this->label);

	this->setContentSize(this->label->getContentSize());

	this->initializeListeners();
}

MenuLabel::~MenuLabel()
{
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

void MenuLabel::initializeListeners()
{
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = CC_CALLBACK_1(MenuLabel::onMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MenuLabel::onMouseDown, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void MenuLabel::onMouseMove(EventMouse* event)
{
	if (this->menuOnMouseClick != nullptr && this->isVisible())
	{
		if (Utils::intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
		{
			this->labelHighlighted->enableOutline(*highlightColor, highlightOutlineSize);
		}
		else
		{
			this->labelHighlighted->enableOutline(Color4B::BLACK, 1);
		}
	}
}

void MenuLabel::onMouseDown(EventMouse* event)
{
	if (this->menuOnMouseClick != nullptr && this->isVisible())
	{
		if (Utils::intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
		{
			this->menuOnMouseClick(this);
		}
	}
}
