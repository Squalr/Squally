#pragma once
#include <functional>
#include <vector>

#include "Engine/SmartNode.h"

class ClickableNode;

class CCheckbox : public SmartNode
{
public:
	static CCheckbox * create(ClickableNode* uncheckedButton, ClickableNode* checkedButton, bool initialState,
			std::function<bool(CCheckbox*, bool)> callback = nullptr);

	void setCallback(std::function<bool(CCheckbox*, bool)> callback);
	void setToggled(bool isToggled);
	bool getToggled();

protected:
	CCheckbox(ClickableNode* uncheckedButton, ClickableNode* checkedButton, bool initialState,
			std::function<bool(CCheckbox*, bool)> callback);
	virtual ~CCheckbox();

private:
	typedef SmartNode super;
	void onToggle();
	void onUntoggle();
	void updateVisuals();

	ClickableNode* onSwitch;
	ClickableNode* offSwitch;

	bool isToggled;
	std::function<bool(CCheckbox*, bool)> toggleCallback;
	std::vector<ClickableNode*>* clickableMenus;
};

