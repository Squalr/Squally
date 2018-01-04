#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/MenuSprite.h"

using namespace cocos2d;

class RadioButton : public Node
{
public:
	static RadioButton * create(int groupIdentifier);

	void check();
	void uncheck();
	void setCheckCallback(std::function<void(RadioButton*)> callback);

	const std::string RadioButtonCheckEvent = "radio_button_check_event";

private:
	RadioButton(int groupIdentifier);
	~RadioButton();

	void onGroupCheck(EventCustom* event);
	void onUncheckClick(MenuSprite* menuSprite);
	void onCheckClick(MenuSprite* menuSprite);
	void initializeListeners();

	MenuSprite * unchecked;
	MenuSprite * checked;
	bool isChecked;

	int groupId;
	std::function<void(RadioButton*)> onCheckCallback;
};

