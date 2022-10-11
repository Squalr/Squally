#pragma once
#include <functional>
#include <vector>

#include "Engine/SmartNode.h"

class Checkbox;

class ToggleGroup : public SmartNode
{
public:
	static ToggleGroup* create(std::function<void(Checkbox*)> callback);

	void addToggle(Checkbox* toggle);

protected:
	ToggleGroup(std::function<void(Checkbox*)> callback);
	virtual ~ToggleGroup();
	
private:
	typedef SmartNode super;

	bool onToggleClick(Checkbox* toggle, bool isToggled);

	std::function<void(Checkbox*)> callback = nullptr;
	Checkbox* activeToggle = nullptr;
	std::vector<Checkbox*> toggles;
};

