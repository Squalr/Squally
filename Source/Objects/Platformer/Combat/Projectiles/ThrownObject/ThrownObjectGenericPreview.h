#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class ThrownObjectGenericPreview : public HackablePreview
{
public:
	static ThrownObjectGenericPreview* create(std::string objectResource);

	HackablePreview* clone() override;

protected:
	ThrownObjectGenericPreview(std::string objectResource);
	virtual ~ThrownObjectGenericPreview();
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	std::string objectResource;
	cocos2d::Sprite* objectPreview;
};
