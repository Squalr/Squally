#pragma once
#include <functional>
#include <vector>

#include "Engine/SmartNode.h"

class CCheckbox;

class ToggleGroup : public SmartNode
{
public:
	static ToggleGroup * create(std::function<void(CCheckbox*)> callback);

	void addToggle(CCheckbox* toggle);

private:
	typedef SmartNode super;
	ToggleGroup(std::function<void(CCheckbox*)> callback);
	virtual ~ToggleGroup();

	bool onToggleClick(CCheckbox* toggle, bool isToggled);

	std::function<void(CCheckbox*)> callback;
	CCheckbox* activeToggle;
	std::vector<CCheckbox*> toggles;
};

