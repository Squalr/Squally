#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/HexusEvents.h"
#include "Events/NavigationEvents.h"
#include "Resources.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/CardStorage.h"

using namespace cocos2d;

class HexusRewardsMenu : public FadeScene
{
public:
	static HexusRewardsMenu * create();

	void onRewardsOpen(EventCustom* eventCustom);
protected:
	HexusRewardsMenu();
	~HexusRewardsMenu();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onRewardSelect(Card* card);
	void onChooseClick(MenuSprite* menuSprite);

	bool backToChapterSelect;
	Sprite* background;
	CardRow* rewardRow;
	MenuSprite* chooseButton;
	Label* selectRewardLabel;
	Card* selectedCard;
};
