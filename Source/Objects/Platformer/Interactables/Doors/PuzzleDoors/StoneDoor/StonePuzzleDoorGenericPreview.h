#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class StonePuzzleDoorGenericPreview : public HackablePreview
{
public:
	static StonePuzzleDoorGenericPreview* create();

	HackablePreview* clone() override;

protected:
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	StonePuzzleDoorGenericPreview();
	virtual ~StonePuzzleDoorGenericPreview();
};
