#include "MouseOverPanel.h"

MouseOverPanel * MouseOverPanel::create(Node* visibleContent, Node* mouseOverContent, Node* panelParent, Size size)
{
	MouseOverPanel* outlineLabel = new MouseOverPanel(visibleContent, mouseOverContent, panelParent, size);

	outlineLabel->autorelease();

	return outlineLabel;
}

MouseOverPanel::MouseOverPanel(Node* visibleContent, Node* mouseOverContent, Node* panelParent, Size size)
{
	this->content = visibleContent;
	this->panelContent = mouseOverContent;
	this->panelParentHost = panelParent;
	this->panelBackgroundFrame = LayerColor::create(Color4B(50, 50, 225, 196), size.width + MouseOverPanel::frameWidth * 2, size.height + MouseOverPanel::frameWidth * 2);
	this->panelBackground = LayerColor::create(Color4B(0, 0, 0, 196), size.width, size.height);

	this->addChild(this->content);
	panelParentHost->addChild(this->panelBackgroundFrame);
	panelParentHost->addChild(this->panelBackground);
	panelParentHost->addChild(this->panelContent);

	this->panelBackgroundFrame->setPositionX(this->content->getPosition().x - MouseOverPanel::frameWidth);
	this->panelBackgroundFrame->setPositionY(this->content->getPosition().y - size.height / 2 - MouseOverPanel::frameWidth);
	this->panelBackground->setPositionX(this->content->getPosition().x);
	this->panelBackground->setPositionY(this->content->getPosition().y - size.height / 2);
	this->panelContent->setPosition(this->content->getPosition() + Vec2(size.width / 2, 0));

	this->panelBackgroundFrame->setVisible(false);
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

	if (GameUtils::isVisible(this) && GameUtils::intersectsV2(this->content, Vec2(args->mouseX, args->mouseY)))
	{
		this->panelBackgroundFrame->setVisible(true);
		this->panelBackground->setVisible(true);
		this->panelContent->setVisible(true);
	}
	else
	{
		this->panelBackgroundFrame->setVisible(false);
		this->panelBackground->setVisible(false);
		this->panelContent->setVisible(false);
	}
}
