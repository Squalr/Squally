#include "ToggleGroup.h"

#include "cocos/base/ccMacros.h"

#include "Engine/SmartNode.h"
#include "Engine/UI/Controls/CCheckbox.h"

using namespace cocos2d;

ToggleGroup* ToggleGroup::create(std::function<void(CCheckbox*)> callback)
{
	ToggleGroup* instance = new ToggleGroup(callback);

	instance->autorelease();

	return instance;
}

ToggleGroup::ToggleGroup(std::function<void(CCheckbox*)> callback)
{
	this->toggles = std::vector<CCheckbox*>();
	this->callback = callback;
}

ToggleGroup::~ToggleGroup()
{
}

void ToggleGroup::addToggle(CCheckbox* toggle)
{
	toggle->setCallback(CC_CALLBACK_2(ToggleGroup::onToggleClick, this));

	this->toggles.push_back(toggle);

	this->addChild(toggle);
}

bool ToggleGroup::onToggleClick(CCheckbox* toggle, bool willToggle)
{
	// Disable all other toggles
	for (auto it = this->toggles.begin(); it != this->toggles.end(); it++)
	{
		if (*it != toggle)
		{
			(*it)->setToggled(false);
		}
	}

	// One toggle must always be active -- always return true (remain toggled) if attempting to deactivate the only active toggle in this group
	if (toggle->getToggled() && !willToggle)
	{
		willToggle = true;
	}

	if (willToggle && this->callback != nullptr)
	{
		// Trigger the callback indicating the active toggle in this group has changed
		this->callback(toggle);
	}

	return willToggle;
}
