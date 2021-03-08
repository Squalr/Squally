#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class IcicleGenericPreview : public HackablePreview
{
public:
	static IcicleGenericPreview* create();

	HackablePreview* clone() override;

protected:
	IcicleGenericPreview();
	virtual ~IcicleGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* previewAsteroid;
};
