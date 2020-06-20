#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class ConstantString;
class LocalizedLabel;
class LocalizedString;
class PlatformerEntity;
class StatsBars;

class PartyMenu : public SmartNode
{
public:
	static PartyMenu* create();

	void open();
	void openForSelection(std::string iconResource, int count, std::function<bool(PlatformerEntity*)> canSelect, std::function<void(PlatformerEntity*)> onSelect, std::function<void()> onExit);
	void disableUnstuck();
	void setReturnClickCallback(std::function<void()> returnClickCallback);
	int getSelectionIndex();
	void setSelectionIndex(int index);

	static std::string UnstuckMap;

protected:
	PartyMenu();
	virtual ~PartyMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void select(StatsBars* statsBars);
	void buildAllStats();
	void buildStats(PlatformerEntity* entity);
	void trySelectNext();
	void trySelectPrevious();
	void performSelectionActions();
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
	ConstantString* countString;
	LocalizedLabel* countLabel;

	std::vector<StatsBars*> partyStatsBars;

	int selectionIndex;

	std::function<void(PlatformerEntity*)> onSelect;
	std::function<void()> onExit;
	std::function<void()> returnClickCallback;
};
