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

void MenuLabel::SetCallback(std::function<void(MenuLabel*)> callback)
{
	this->menuOnMouseClick = callback;
}

void MenuLabel::SetText(std::string text)
{
	this->label->setString(text);
	this->labelHighlighted->setString(text);

	this->setContentSize(this->label->getContentSize());
}

void MenuLabel::onEnter()
{
	Node::onEnter();

	this->InitializeListeners();
}

void MenuLabel::InitializeListeners()
{
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = CC_CALLBACK_1(MenuLabel::OnMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MenuLabel::OnMouseDown, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void MenuLabel::OnMouseMove(EventMouse* event)
{
	if (this->menuOnMouseClick != nullptr && this->isVisible())
	{
		if (Utils::Intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
		{
			this->labelHighlighted->enableOutline(*highlightColor, highlightOutlineSize);
		}
		else
		{
			this->labelHighlighted->enableOutline(Color4B::BLACK, 1);
		}
	}
}

void MenuLabel::OnMouseDown(EventMouse* event)
{
	if (this->menuOnMouseClick != nullptr && this->isVisible())
	{
		if (Utils::Intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
		{
			this->menuOnMouseClick(this);
		}
	}
}
