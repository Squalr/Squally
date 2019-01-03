#pragma once
#include <string>

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class LayerColor;
}

class LocalizedLabel;
class LocalizedString;

class BannerBase : public ComponentBase
{
public:
	static BannerBase* create();

protected:
	BannerBase();
	~BannerBase();

	void onEnter() override;
	void initializePositions() override;
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;
	void setBannerText(LocalizedString* text);
	void flashBanner();
	void showBanner();
	void hideBanner();
	void addBannerChild(Node* child);

private:
	cocos2d::LayerColor* bannerOverlay;
	LocalizedLabel* bannerLabel;
	cocos2d::Node* bannerChildrenNode;
};
