#pragma once
#include "cocos2d.h"

#include "Engine/GlobalScene.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/CardStorage.h"

using namespace cocos2d;

class HexusRewardsMenu : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	HexusRewardsMenu();
	~HexusRewardsMenu();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onRewardsOpen(int reward, bool isRewardReduced);
	void onReturnClick(MenuSprite* menuSprite);

	Sprite* background;
	Sprite* goldSprite;
	Sprite* goldSpriteLesser;
	Label* goldLabel;
	MenuSprite* returnButton;

	static HexusRewardsMenu* instance;
	static const std::string KeyScheduleHexusGoldTick;
};
