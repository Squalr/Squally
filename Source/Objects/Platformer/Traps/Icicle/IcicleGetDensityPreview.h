#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class IcicleGetDensityPreview : public HackablePreview
{
public:
	static IcicleGetDensityPreview* create();

	HackablePreview* clone() override;

protected:
	IcicleGetDensityPreview();
	virtual ~IcicleGetDensityPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* previewAsteroid = nullptr;
	LocalizedLabel* xmm0Top = nullptr;
	LocalizedLabel* xmm0Bottom = nullptr;
};
