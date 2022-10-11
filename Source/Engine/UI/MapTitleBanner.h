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

protected:
	MapTitleBanner(LocalizedString* bannerString);
	virtual ~MapTitleBanner();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef GameObject super;

	LocalizedString* bannerString = nullptr;
	LocalizedLabel* bannerLabel = nullptr;
	cocos2d::Node* contentNode = nullptr;
	cocos2d::DrawNode* bannerBarTop = nullptr;
	cocos2d::DrawNode* bannerBarBottom = nullptr;
	Hud* hud = nullptr;

	bool hasRelocated = false;

	static const float BannerBarHeight;
};
