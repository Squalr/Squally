#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/MenuSprite.h"

using namespace cocos2d;

class RadioButton : public Node
{
public:
	static RadioButton * create(int groupIdentifier);

	void Check();
	void Uncheck();
	void SetCheckCallback(std::function<void(RadioButton*)> callback);

	const std::string RadioButtonCheckEvent = "radio_button_check_event";

private:
	RadioButton(int groupIdentifier);
	~RadioButton();
	void OnGroupCheck(EventCustom* event);
	void OnUncheck(MenuSprite* menuSprite);
	void OnCheck(MenuSprite* menuSprite);
	void InitializeListeners();
	void UncheckSilent();

	MenuSprite * unchecked;
	MenuSprite * checked;

	int groupId;
	std::function<void(RadioButton*)> onCheckCallback;
};

