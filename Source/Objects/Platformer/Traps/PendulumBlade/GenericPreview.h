#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class GenericPreview : public HackablePreview
{
public:
	static GenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	GenericPreview();
	~GenericPreview() = default;
	void onEnter() override;

	cocos2d::Sprite* previewBlade;
};
