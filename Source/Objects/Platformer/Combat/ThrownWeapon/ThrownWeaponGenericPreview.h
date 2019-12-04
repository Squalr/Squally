#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class ThrownWeaponGenericPreview : public HackablePreview
{
public:
	static ThrownWeaponGenericPreview* create(std::string weaponResource);

	HackablePreview* clone() override;

protected:
	ThrownWeaponGenericPreview(std::string weaponResource);
	virtual ~ThrownWeaponGenericPreview();
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	std::string weaponResource;
	cocos2d::Sprite* bomberTorch;
};
