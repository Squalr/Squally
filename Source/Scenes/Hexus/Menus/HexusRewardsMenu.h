#pragma once
#include <string>

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ConstantString;
class LocalizedLabel;
class Sound;

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
	void onRewardsOpen(int reward, bool isRewardReduced, bool isChapterClear);
	void onReturnClick();

	cocos2d::Sprite* background;
	cocos2d::Sprite* goldSprite;
	cocos2d::Sprite* goldSpriteLesser;
	cocos2d::Sprite* goldSpriteChapterClear;
	ConstantString* goldString;
	LocalizedLabel* goldLabel;
	ClickableNode* returnButton;
	Sound* rewardSound;

	static HexusRewardsMenu* instance;
	static const std::string KeyScheduleHexusGoldTick;
};
