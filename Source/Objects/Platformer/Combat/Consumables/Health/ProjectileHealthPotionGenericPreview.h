#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class ProjectileHealthPotionGenericPreview : public HackablePreview
{
public:
	static ProjectileHealthPotionGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ProjectileHealthPotionGenericPreview();
	virtual ~ProjectileHealthPotionGenericPreview();
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* healthPotion;
};
