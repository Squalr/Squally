#pragma once
#include <functional>

#include "Engine/SmartNode.h"

class ClickableNode;

namespace cocos2d
{
	class EventCustom;
}

class CRadioButton : public SmartNode
{
public:
	static CRadioButton * create(int groupIdentifier);

	void check();
	void uncheck();
	void setCheckCallback(std::function<void(CRadioButton*)> callback);

	const std::string RadioButtonCheckEvent = "radio_button_check_event";

private:
	typedef SmartNode super;
	CRadioButton(int groupIdentifier);
	virtual ~CRadioButton();

	void initializeListeners() override;
	void onGroupCheck(cocos2d::EventCustom* event);
	void onUncheckClick(ClickableNode* menuSprite);
	void onCheckClick(ClickableNode* menuSprite);

	ClickableNode * unchecked;
	ClickableNode * checked;
	bool isChecked;

	int groupId;
	std::function<void(CRadioButton*)> onCheckCallback;
};

