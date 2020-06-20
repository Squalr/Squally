#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class FogOfWarGenericPreview : public HackablePreview
{
public:
	static FogOfWarGenericPreview* create();

	HackablePreview* clone() override;

protected:
	FogOfWarGenericPreview();
	virtual ~FogOfWarGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* fog;
};
