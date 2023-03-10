#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class ArrowVolleyGenericPreview : public HackablePreview
{
public:
	static ArrowVolleyGenericPreview* create(std::string arrowResource);

	HackablePreview* clone() override;

protected:
	ArrowVolleyGenericPreview(std::string arrowResource);
	virtual ~ArrowVolleyGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* arrow = nullptr;
	std::string arrowResource;
};
