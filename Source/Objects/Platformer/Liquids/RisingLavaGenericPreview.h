#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class RisingLavaGenericPreview : public HackablePreview
{
public:
	static RisingLavaGenericPreview* create();

	HackablePreview* clone() override;

protected:
	RisingLavaGenericPreview();
	virtual ~RisingLavaGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
