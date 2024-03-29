#include "RadioButton.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableNode.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string RadioButton::RadioButtonCheckEvent = "EVENT_CHECK_RADIO_BUTTON";

RadioButton* RadioButton::create(ClickableNode* checked, ClickableNode* unchecked, int groupIdentifier)
{
	RadioButton* instance = new RadioButton(checked, unchecked, groupIdentifier);

	instance->autorelease();

	return instance;
}

RadioButton::RadioButton(ClickableNode* checked, ClickableNode* unchecked, int groupIdentifier)
{
	this->groupId = groupIdentifier;

	this->checked = checked;
	this->unchecked = unchecked;

	this->checked->setMouseClickCallback(CC_CALLBACK_0(RadioButton::onUncheckClick, this));
	this->unchecked->setMouseClickCallback(CC_CALLBACK_0(RadioButton::onCheckClick, this));

	this->isChecked = false;
	this->checked->setVisible(false);

	this->addChild(this->unchecked);
	this->addChild(this->checked);
}

RadioButton::~RadioButton()
{
}

void RadioButton::initializeListeners()
{
	SmartNode::initializeListeners();

	EventListenerCustom* customListener = EventListenerCustom::create(this->RadioButtonCheckEvent, CC_CALLBACK_1(RadioButton::onGroupCheck, this));

	this->addEventListener(customListener);
}

void RadioButton::setCheckCallback(std::function<void(RadioButton*)> callback)
{
	this->onCheckCallback = callback;
}

void RadioButton::onGroupCheck(EventCustom* event)
{
	int* eventGroupId = static_cast<int*>(event->getData());

	if (*eventGroupId == this->groupId)
	{
		this->uncheck();
	}
}

void RadioButton::onCheckClick()
{
	this->check();
}

void RadioButton::onUncheckClick()
{
	// No actions required
}

void RadioButton::check(bool invokeCallback)
{
	if (!this->isChecked)
	{
		this->getEventDispatcher()->dispatchEvent(this->RadioButtonCheckEvent, &this->groupId);

		this->checked->setVisible(true);
		this->unchecked->setVisible(false);

		if (invokeCallback && this->onCheckCallback != nullptr)
		{
			this->onCheckCallback(this);
		}

		this->isChecked = true;
	}
}

void RadioButton::uncheck()
{
	this->checked->setVisible(false);
	this->unchecked->setVisible(true);

	this->isChecked = false;
}

void RadioButton::enableInteraction()
{
	this->checked->enableInteraction();
	this->unchecked->enableInteraction();
}

void RadioButton::disableInteraction()
{
	this->checked->disableInteraction();
	this->unchecked->disableInteraction();
}
