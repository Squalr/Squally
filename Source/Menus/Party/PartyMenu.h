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

	cocos2d::Sprite* partyWindow = nullptr;
	LocalizedLabel* partyLabel = nullptr;
	cocos2d::Node* statsBarsNode = nullptr;
	ClickableNode* closeButton = nullptr;
	ClickableTextNode* cancelButton = nullptr;
	ClickableTextNode* returnButton = nullptr;
	ClickableTextNode* stuckButton = nullptr;
	
	cocos2d::Node* chooseTargetNode = nullptr;
	cocos2d::Sprite* chooseTargetFrame = nullptr;
	cocos2d::Sprite* chooseTargetItemFrame = nullptr;
	cocos2d::Sprite* chooseTargetItemIcon = nullptr;
	LocalizedLabel* chooseTargetLabel = nullptr;
	ConstantString* countString = nullptr;
	LocalizedLabel* countLabel = nullptr;

	std::vector<StatsBars*> partyStatsBars;

	int selectionIndex = 0;

	std::function<void(PlatformerEntity*)> onSelect = nullptr;
	std::function<void()> onExit = nullptr;
	std::function<void()> returnClickCallback = nullptr;
};
