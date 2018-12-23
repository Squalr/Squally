#pragma once
#include <string>

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class LayerColor;
}

class LocalizedLabel;

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
	void setBannerText(std::string text);
	void flashBanner();
	void showBanner();
	void hideBanner();
	void addBannerChild(Node* child);

private:
	cocos2d::LayerColor* statusBanner;
	LocalizedLabel* statusLabel;
	cocos2d::Node* bannerChildrenNode;
};
