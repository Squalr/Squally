#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class ArrowRainGenericPreview : public HackablePreview
{
public:
	static ArrowRainGenericPreview* create(std::string arrowResource);

	HackablePreview* clone() override;

protected:
	ArrowRainGenericPreview(std::string arrowResource);
	virtual ~ArrowRainGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* arrow;
	std::string arrowResource;
};
