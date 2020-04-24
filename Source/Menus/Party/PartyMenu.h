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

	void buildStats(PlatformerEntity* entity);

	cocos2d::Sprite* partyWindow;
	LocalizedLabel* partyLabel;
	cocos2d::Node* statsBarsNode;
	ClickableNode* closeButton;
	ClickableTextNode* returnButton;
	ClickableTextNode* stuckButton;

	std::vector<StatsBars*> partyStatsBars;

	std::function<void()> returnClickCallback;
};
