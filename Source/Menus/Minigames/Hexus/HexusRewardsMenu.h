#pragma once
#include "cocos2d.h"

#include "Engine/GlobalScene.h"

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
