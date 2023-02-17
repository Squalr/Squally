#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;

class BatSwarmGenericPreview : public HackablePreview
{
public:
	static BatSwarmGenericPreview* create();

	HackablePreview* clone() override;

protected:
	BatSwarmGenericPreview();
	virtual ~BatSwarmGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	PlatformerEntity* bat = nullptr;
};
