#include "InputOutputPanel.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Input/ClickableNode.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Components/Letters/SmartAsciiLabel.h"

#include "Resources/CipherResources.h"
#include "Resources/UIResources.h"

#include "Strings/Cipher/Inputs.h"
#include "Strings/Cipher/Outputs.h"

using namespace cocos2d;

InputOutputPanel* InputOutputPanel::create(unsigned char input, unsigned char output, std::function<void(InputOutputPanel*)> selectCallback)
{
	InputOutputPanel* instance = new InputOutputPanel(input, output, selectCallback);

	instance->autorelease();

	return instance;
}

InputOutputPanel::InputOutputPanel(unsigned char input, unsigned char output, std::function<void(InputOutputPanel*)> selectCallback)
{
	this->input = input;
	this->output = output;
	this->selectCallback = selectCallback;

	this->panel = ClickableNode::create(CipherResources::IOPanel, CipherResources::IOPanelSelected);
	this->inputLabel = SmartAsciiLabel::create();
	this->outputLabel = SmartAsciiLabel::create();
	this->failedIcon = Sprite::create(CipherResources::IOFailed);
	this->passedIcon = Sprite::create(CipherResources::IOCorrect);

	this->inputLabel->loadDisplayValue(this->input, CipherEvents::DisplayDataType::Ascii);
	this->outputLabel->loadDisplayValue(this->output, CipherEvents::DisplayDataType::Ascii);

	this->addChild(this->panel);
	this->addChild(this->inputLabel);
	this->addChild(this->outputLabel);
	this->addChild(this->failedIcon);
	this->addChild(this->passedIcon);
}

InputOutputPanel::~InputOutputPanel()
{
}

void InputOutputPanel::onEnter()
{
	super::onEnter();

	this->failedIcon->setVisible(false);
	this->passedIcon->setVisible(false);
}

void InputOutputPanel::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->inputLabel->setPosition(Vec2(-64.0f, 0.0f));
	this->outputLabel->setPosition(Vec2(64.0f, 0.0f));
	this->failedIcon->setPosition(Vec2(144.0f, 4.0f));
	this->passedIcon->setPosition(Vec2(144.0f, 4.0f));
}

void InputOutputPanel::initializeListeners()
{
	super::initializeListeners();

	this->panel->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->selectCallback != nullptr)
		{
			this->selectCallback(this);
		}
	});
}

void InputOutputPanel::enableInteraction()
{
	this->panel->enableInteraction();
}

void InputOutputPanel::disableInteraction()
{
	this->panel->disableInteraction();
}

void InputOutputPanel::setStatusPassed()
{
	this->failedIcon->setVisible(false);
	this->passedIcon->setVisible(true);
}

void InputOutputPanel::setStatusFailed()
{
	this->failedIcon->setVisible(true);
	this->passedIcon->setVisible(false);
}

void InputOutputPanel::clearStatus()
{
	this->failedIcon->setVisible(false);
	this->passedIcon->setVisible(false);
}
