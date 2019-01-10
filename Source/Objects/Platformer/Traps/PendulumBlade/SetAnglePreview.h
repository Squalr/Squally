#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class SetAnglePreview : public HackablePreview
{
public:
	static SetAnglePreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	SetAnglePreview();
	~SetAnglePreview() = default;

	cocos2d::Sprite* previewBlade;
};
