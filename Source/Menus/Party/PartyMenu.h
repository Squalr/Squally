#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class LocalizedLabel;
class LocalizedString;
class PlatformerEntity;
class StatsBars;

class PartyMenu : public SmartNode
{
public:
	static PartyMenu* create();

	void open();
	void openForSelection(std::string iconResource, std::function<bool(PlatformerEntity*)> canSelect, std::function<void(PlatformerEntity*)> onSelect, std::function<void()> onExit);
	void disableUnstuck();
	void setReturnClickCallback(std::function<void()> returnClickCallback);

	static std::string UnstuckMap;

protected:
	PartyMenu();
	virtual ~PartyMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void buildAllStats();
	void buildStats(PlatformerEntity* entity);
	void onCancelClick();
	void onReturnClick();

	cocos2d::Sprite* partyWindow;
	LocalizedLabel* partyLabel;
	cocos2d::Node* statsBarsNode;
	ClickableNode* closeButton;
	ClickableTextNode* cancelButton;
	ClickableTextNode* returnButton;
	ClickableTextNode* stuckButton;
	
	cocos2d::Node* chooseTargetNode;
	cocos2d::Sprite* chooseTargetFrame;
	cocos2d::Sprite* chooseTargetItemFrame;
	cocos2d::Sprite* chooseTargetItemIcon;
	LocalizedLabel* chooseTargetLabel;

	std::vector<StatsBars*> partyStatsBars;

	std::function<void(PlatformerEntity*)> onSelect;
	std::function<void()> onExit;
	std::function<void()> returnClickCallback;
};
