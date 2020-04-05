#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class SmartAnimationSequenceNode;

class TimeBombTickPreview : public HackablePreview
{
public:
	static TimeBombTickPreview* create();

	HackablePreview* clone() override;

protected:
	TimeBombTickPreview();
	virtual ~TimeBombTickPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* timeBomb;
	LocalizedLabel* tick;
};
