#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class RegenerationGenericPreview : public HackablePreview
{
public:
	static RegenerationGenericPreview* create(std::string arrowResource);

	HackablePreview* clone() override;

protected:
	RegenerationGenericPreview(std::string arrowResource);
	virtual ~RegenerationGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* arrow;
	std::string arrowResource;
};
