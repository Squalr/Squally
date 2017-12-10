#include "MenuLabel.h"
#include "Resources.h"

const Color4B highlightColor(255, 255, 168, 255);
const float fontOutlineSize = 2.0f;
const float highlightOutlineSize = 4.0f;

MenuLabel::MenuLabel(std::string labelText, std::string fontResource, float fontSize)
{
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

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void MenuLabel::OnMouseMove(EventMouse* event)
{
	Rect mouseRect = Rect(event->getCursorX(), event->getCursorY(), 1.0f, 1.0f);

	Vec2 origin = this->convertToWorldSpace(Vec2(this->label->getBoundingBox().origin.x, this->label->getBoundingBox().origin.y));
	Rect labelRect = Rect(origin.x, origin.y, this->label->getContentSize().width, this->label->getContentSize().height);

	if (labelRect.intersectsRect(mouseRect))
	{
		this->labelHighlighted->enableOutline(highlightColor, highlightOutlineSize);
	}
	else
	{
		this->labelHighlighted->enableOutline(Color4B::BLACK, 1);
	}
}
