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
	static RadioButton* create(ClickableNode* checked, ClickableNode* unchecked, int groupIdentifier);

	void check(bool invokeCallback = true);
	void uncheck();
	void setCheckCallback(std::function<void(RadioButton*)> callback);
	void enableInteraction();
	void disableInteraction();

	static const std::string RadioButtonCheckEvent;

protected:
	RadioButton(ClickableNode* checked, ClickableNode* unchecked, int groupIdentifier);
	virtual ~RadioButton();

private:
	typedef SmartNode super;

	void initializeListeners() override;
	void onGroupCheck(cocos2d::EventCustom* event);
	void onUncheckClick();
	void onCheckClick();

	ClickableNode* checked = nullptr;
	ClickableNode* unchecked = nullptr;
	bool isChecked = false;

	int groupId = 0;
	std::function<void(RadioButton*)> onCheckCallback = nullptr;
};
