#include "MouseOverPanel.h"

#include "cocos2d.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/SmartNode.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

MouseOverPanel * MouseOverPanel::create(Node* visibleContent, Node* mouseOverContent, Node* panelParent, Size size)
{
	MouseOverPanel* instance = new MouseOverPanel(visibleContent, mouseOverContent, panelParent, size);

	instance->autorelease();

	return instance;
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
}

MouseOverPanel::~MouseOverPanel()
{
}

void MouseOverPanel::initializeListeners()
{
	SmartNode::initializeListeners();

	EventListenerCustom* mouseMoveListener = EventListenerCustom::create(MouseEvents::MouseMoveEvent, CC_CALLBACK_1(MouseOverPanel::onMouseMove, this));

	this->addEventListener(mouseMoveListener);
}

void MouseOverPanel::onMouseMove(EventCustom* event)
{
	MouseEvents::MouseEventArgs* args = static_cast<MouseEvents::MouseEventArgs*>(event->getUserData());

	if (GameUtils::isVisible(this) && GameUtils::intersectsV2(this->content, args->mouseCoords))
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
