#include "MouseOverPanel.h"

MouseOverPanel * MouseOverPanel::create(Node* visibleContent, Node* mouseOverContent, Vec2 size)
{
	MouseOverPanel* outlineLabel = new MouseOverPanel(visibleContent, mouseOverContent, size);

	outlineLabel->autorelease();

	return outlineLabel;
}

MouseOverPanel::MouseOverPanel(Node* visibleContent, Node* mouseOverContent, Vec2 size)
{
	this->content = visibleContent;
	this->panelContent = mouseOverContent;
	this->panelBackground = Sprite::create(Resources::Menus_HackerModeMenu_MouseOverPanel);

	this->addChild(this->content);
	this->addChild(this->panelBackground);
	this->addChild(this->panelContent);

	this->panelBackground->setScaleX(size.x / this->panelBackground->getContentSize().width);
	this->panelBackground->setScaleY(size.y / this->panelBackground->getContentSize().height);

	this->panelBackground->setVisible(false);
	this->panelContent->setVisible(false);

	this->initializeListeners();
}

MouseOverPanel::~MouseOverPanel()
{
}

void MouseOverPanel::initializeListeners()
{
	EventListenerCustom* customListener = EventListenerCustom::create(Mouse::MouseMoveEvent, CC_CALLBACK_1(MouseOverPanel::onMouseSpriteMove, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(customListener, this);
}

void MouseOverPanel::onMouseSpriteMove(EventCustom* event)
{
	Mouse::MouseEventArgs* args = static_cast<Mouse::MouseEventArgs*>(event->getUserData());

	if (Utils::isVisible(this) && Utils::intersectsV2(this->content, Vec2(args->mouseX, args->mouseY)))
	{
		this->panelBackground->setVisible(true);
		this->panelContent->setVisible(true);
	}
	else
	{
		this->panelBackground->setVisible(false);
		this->panelContent->setVisible(false);
	}
}
