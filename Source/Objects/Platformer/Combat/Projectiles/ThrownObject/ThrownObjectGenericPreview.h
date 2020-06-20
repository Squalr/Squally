#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class ThrownObjectGenericPreview : public HackablePreview
{
public:
	static ThrownObjectGenericPreview* create(cocos2d::Node* object);

	HackablePreview* clone() override;

protected:
	ThrownObjectGenericPreview(cocos2d::Node* object);
	virtual ~ThrownObjectGenericPreview();
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Node* object;
};
