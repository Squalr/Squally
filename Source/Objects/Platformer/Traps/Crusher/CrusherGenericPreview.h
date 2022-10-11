#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class SmartClippingNode;

class CrusherGenericPreview : public HackablePreview
{
public:
	static CrusherGenericPreview* create();

	HackablePreview* clone() override;

protected:
	CrusherGenericPreview();
	virtual ~CrusherGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartClippingNode* poleClip = nullptr;
	cocos2d::Sprite* base = nullptr;
	cocos2d::Sprite* pole = nullptr;
	cocos2d::Sprite* crusher = nullptr;

	static const float TravelDistance;
};
