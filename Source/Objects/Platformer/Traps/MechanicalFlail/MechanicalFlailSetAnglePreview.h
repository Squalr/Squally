#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class MechanicalFlailSetAnglePreview : public HackablePreview
{
public:
	static MechanicalFlailSetAnglePreview* create();

	HackablePreview* clone() override;

protected:
	MechanicalFlailSetAnglePreview();
	virtual ~MechanicalFlailSetAnglePreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* previewFlail;
	cocos2d::Sprite* previewJoint;
	LocalizedLabel* eax0Degrees;
	LocalizedLabel* eax90Degrees;
	LocalizedLabel* eax180Degrees;
	LocalizedLabel* eax270Degrees;
};
