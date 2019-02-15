#pragma once
#include <functional>
#include <vector>

#include "Engine/SmartNode.h"

class ClickableNode;

class Checkbox : public SmartNode
{
public:
	static Checkbox * create(ClickableNode* uncheckedButton, ClickableNode* checkedButton, bool initialState,
			std::function<bool(Checkbox*, bool)> callback = nullptr);

	void setCallback(std::function<bool(Checkbox*, bool)> callback);
	void setToggled(bool isToggled);
	bool getToggled();

protected:
	Checkbox(ClickableNode* uncheckedButton, ClickableNode* checkedButton, bool initialState,
			std::function<bool(Checkbox*, bool)> callback);
	virtual ~Checkbox();

private:
	typedef SmartNode super;
	void onToggle();
	void onUntoggle();
	void updateVisuals();

	ClickableNode* onSwitch;
	ClickableNode* offSwitch;

	bool isToggled;
	std::function<bool(Checkbox*, bool)> toggleCallback;
	std::vector<ClickableNode*>* clickableMenus;
};

