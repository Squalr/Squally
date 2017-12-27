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
	void onUncheck(MenuSprite* menuSprite);
	void onCheck(MenuSprite* menuSprite);
	void initializeListeners();
	void uncheckSilent();

	MenuSprite * unchecked;
	MenuSprite * checked;

	int groupId;
	std::function<void(RadioButton*)> onCheckCallback;
};

