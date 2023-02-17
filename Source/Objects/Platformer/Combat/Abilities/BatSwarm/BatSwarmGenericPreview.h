#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class BatSwarmGenericPreview : public HackablePreview
{
public:
	static BatSwarmGenericPreview* create(std::string arrowResource);

	HackablePreview* clone() override;

protected:
	BatSwarmGenericPreview(std::string arrowResource);
	virtual ~BatSwarmGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* arrow = nullptr;
	std::string arrowResource;
};
