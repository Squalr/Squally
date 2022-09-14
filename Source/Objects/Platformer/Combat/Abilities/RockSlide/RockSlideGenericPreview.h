#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class RockSlideGenericPreview : public HackablePreview
{
public:
	static RockSlideGenericPreview* create(std::string rockResource);

	HackablePreview* clone() override;

protected:
	RockSlideGenericPreview(std::string rockResource);
	virtual ~RockSlideGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* rock = nullptr;
	std::string rockResource;
};
