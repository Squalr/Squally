#pragma once
#include "cocos2d.h"

#include "Resources.h"

#include "MenuSprite.h"

using namespace cocos2d;

class CRadioButton : public Node
{
public:
	static CRadioButton * create(int groupIdentifier);

	void check();
	void uncheck();
	void setCheckCallback(std::function<void(CRadioButton*)> callback);

	const std::string RadioButtonCheckEvent = "radio_button_check_event";

private:
	CRadioButton(int groupIdentifier);
	~CRadioButton();

	void onGroupCheck(EventCustom* event);
	void onUncheckClick(MenuSprite* menuSprite);
	void onCheckClick(MenuSprite* menuSprite);
	void initializeListeners();

	MenuSprite * unchecked;
	MenuSprite * checked;
	bool isChecked;

	int groupId;
	std::function<void(CRadioButton*)> onCheckCallback;
};

