#pragma once
#include <string>

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class MenuSprite;

class HexusRewardsMenu : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	HexusRewardsMenu();
	~HexusRewardsMenu();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onRewardsOpen(int reward, bool isRewardReduced);
	void onReturnClick(MenuSprite* menuSprite);

	cocos2d::Sprite* background;
	cocos2d::Sprite* goldSprite;
	cocos2d::Sprite* goldSpriteLesser;
	LocalizedLabel* goldLabel;
	MenuSprite* returnButton;

	static HexusRewardsMenu* instance;
	static const std::string KeyScheduleHexusGoldTick;
};
