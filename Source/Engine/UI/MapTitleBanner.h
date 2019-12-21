#pragma once
#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class DrawNode;
}

class Hud;
class LocalizedLabel;
class LocalizedString;

class MapTitleBanner : public GameObject
{
public:
	static MapTitleBanner* create(LocalizedString* bannerString);

private:
	typedef GameObject super;
	MapTitleBanner(LocalizedString* bannerString);
	~MapTitleBanner();

	void onEnter() override;
	void initializePositions() override;

	LocalizedString* bannerString;
	LocalizedLabel* bannerLabel;
	cocos2d::Node* contentNode;
	cocos2d::DrawNode* bannerBarTop;
	cocos2d::DrawNode* bannerBarBottom;
	Hud* hud;

	bool hasRelocated;

	static const float BannerBarHeight;
};
