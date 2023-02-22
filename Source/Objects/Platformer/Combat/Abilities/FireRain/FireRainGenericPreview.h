#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;

class FireRainGenericPreview : public HackablePreview
{
public:
	static FireRainGenericPreview* create();

	HackablePreview* clone() override;

protected:
	FireRainGenericPreview();
	virtual ~FireRainGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	PlatformerEntity* bat = nullptr;
};
