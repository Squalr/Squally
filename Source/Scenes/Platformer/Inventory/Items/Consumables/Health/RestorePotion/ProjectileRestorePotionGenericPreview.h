#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class ProjectileRestorePotionGenericPreview : public HackablePreview
{
public:
	static ProjectileRestorePotionGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ProjectileRestorePotionGenericPreview();
	~ProjectileRestorePotionGenericPreview();
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* restorePotion;
};
