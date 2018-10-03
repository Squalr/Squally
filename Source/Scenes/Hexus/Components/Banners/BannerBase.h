#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class BannerBase : public ComponentBase
{
public:
	static BannerBase * create();

protected:
	BannerBase();
	~BannerBase();

	void initializePositions() override;
	void onBeforeStateChange(GameState* eventCustom) override;
	void onStateChange(GameState* eventCustom) override;
	void setBannerText(std::string text);
	void flashBanner();
	void showBanner();
	void hideBanner();
	void addBannerChild(Node* child);

private:
	LayerColor* statusBanner;
	Label* statusLabel;
	Node* bannerChildrenNode;
};
