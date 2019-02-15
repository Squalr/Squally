#pragma once
#include <functional>
#include <vector>

#include "Engine/SmartNode.h"

class Checkbox;

class ToggleGroup : public SmartNode
{
public:
	static ToggleGroup * create(std::function<void(Checkbox*)> callback);

	void addToggle(Checkbox* toggle);

private:
	typedef SmartNode super;
	ToggleGroup(std::function<void(Checkbox*)> callback);
	virtual ~ToggleGroup();

	bool onToggleClick(Checkbox* toggle, bool isToggled);

	std::function<void(Checkbox*)> callback;
	Checkbox* activeToggle;
	std::vector<Checkbox*> toggles;
};

