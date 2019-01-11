#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class MechanicalFlailGenericPreview : public HackablePreview
{
public:
	static MechanicalFlailGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	MechanicalFlailGenericPreview();
	~MechanicalFlailGenericPreview() = default;
	void onEnter() override;

	cocos2d::Sprite* previewFlail;
	cocos2d::Sprite* previewJoint;
};
