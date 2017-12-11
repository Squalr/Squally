#include "MenuLabel.h"

MenuLabel::MenuLabel(std::string labelText, std::string fontResource, float fontSize) : MenuLabel(labelText, fontResource, fontSize, nullptr)
{
}

MenuLabel::MenuLabel(std::string labelText, std::string fontResource, float fontSize, std::function<void(MenuLabel*)> onMouseClick)
{
	this->menuOnMouseClick = onMouseClick;

	this->label = Label::createWithTTF(labelText, fontResource, fontSize);
	this->labelHighlighted = Label::createWithTTF(labelText, fontResource, fontSize);

	this->label->enableOutline(Color4B::BLACK, fontOutlineSize);

	this->addChild(this->labelHighlighted);
	this->addChild(this->label);
}

MenuLabel::~MenuLabel()
{
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

bool MenuLabel::Intersects(float mouseX, float mouseY)
{
	Rect mouseRect = Rect(mouseX, mouseY, 1.0f, 1.0f);

	Vec2 origin = this->convertToWorldSpace(Vec2(this->label->getBoundingBox().origin.x, this->label->getBoundingBox().origin.y));
	Rect labelRect = Rect(origin.x, origin.y, this->label->getContentSize().width, this->label->getContentSize().height);

	if (labelRect.intersectsRect(mouseRect))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MenuLabel::OnMouseMove(EventMouse* event)
{
	if (this->menuOnMouseClick != nullptr)
	{
		if (this->Intersects(event->getCursorX(), event->getCursorY()))
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
	if (this->menuOnMouseClick != nullptr)
	{
		if (this->Intersects(event->getCursorX(), event->getCursorY()))
		{
			this->menuOnMouseClick(this);
		}
	}
}
