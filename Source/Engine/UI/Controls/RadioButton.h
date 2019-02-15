#pragma once
#include <functional>

#include "Engine/SmartNode.h"

class ClickableNode;

namespace cocos2d
{
	class EventCustom;
}

class RadioButton : public SmartNode
{
public:
	static RadioButton * create(int groupIdentifier);

	void check();
	void uncheck();
	void setCheckCallback(std::function<void(RadioButton*)> callback);

	const std::string RadioButtonCheckEvent = "radio_button_check_event";

private:
	typedef SmartNode super;
	RadioButton(int groupIdentifier);
	virtual ~RadioButton();

	void initializeListeners() override;
	void onGroupCheck(cocos2d::EventCustom* event);
	void onUncheckClick(ClickableNode* menuSprite);
	void onCheckClick(ClickableNode* menuSprite);

	ClickableNode * unchecked;
	ClickableNode * checked;
	bool isChecked;

	int groupId;
	std::function<void(RadioButton*)> onCheckCallback;
};

