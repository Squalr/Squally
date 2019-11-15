#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class ProjectileSpeedRuneGenericPreview : public HackablePreview
{
public:
	static ProjectileSpeedRuneGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ProjectileSpeedRuneGenericPreview();
	~ProjectileSpeedRuneGenericPreview();
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* speedRune;
};
