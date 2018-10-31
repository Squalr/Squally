#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Engine/UI/Controls/CCheckbox.h"

using namespace cocos2d;

class ToggleGroup : public SmartNode
{
public:
	static ToggleGroup * create(std::function<void(CCheckbox*)> callback);

	void addToggle(CCheckbox* toggle);

private:
	ToggleGroup(std::function<void(CCheckbox*)> callback);
	~ToggleGroup();

	bool onToggleClick(CCheckbox* toggle, bool isToggled);

	std::function<void(CCheckbox*)> callback;
	CCheckbox* activeToggle;
	std::vector<CCheckbox*> toggles;
};

