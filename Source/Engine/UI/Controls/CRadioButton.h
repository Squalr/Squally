#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

class CRadioButton : public SmartNode
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

	void initializeListeners() override;
	void onGroupCheck(EventCustom* event);
	void onUncheckClick(MenuSprite* menuSprite);
	void onCheckClick(MenuSprite* menuSprite);

	MenuSprite * unchecked;
	MenuSprite * checked;
	bool isChecked;

	int groupId;
	std::function<void(CRadioButton*)> onCheckCallback;
};

