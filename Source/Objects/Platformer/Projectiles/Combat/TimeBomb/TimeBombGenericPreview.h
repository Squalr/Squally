#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class TimeBombGenericPreview : public HackablePreview
{
public:
	static TimeBombGenericPreview* create();

	HackablePreview* clone() override;

protected:
	TimeBombGenericPreview();
	virtual ~TimeBombGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* timeBomb;
};
