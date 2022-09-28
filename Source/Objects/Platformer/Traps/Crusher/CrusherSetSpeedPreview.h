#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class SmartClippingNode;

class CrusherSetSpeedPreview : public HackablePreview
{
public:
	static CrusherSetSpeedPreview* create();

	HackablePreview* clone() override;

protected:
	CrusherSetSpeedPreview();
	virtual ~CrusherSetSpeedPreview();

	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;

private:
	typedef HackablePreview super;

	SmartClippingNode* poleClip = nullptr;
	cocos2d::Sprite* base = nullptr;
	cocos2d::Sprite* pole = nullptr;
	cocos2d::Sprite* crusher = nullptr;

	cocos2d::Sprite* previewSqually = nullptr;
	LocalizedLabel* eax0Label = nullptr;
	LocalizedLabel* ebx0Label = nullptr;
	LocalizedLabel* ecx0Label = nullptr;
	LocalizedLabel* eax1Label = nullptr;
	LocalizedLabel* ebx1Label = nullptr;
	LocalizedLabel* ecx1Label = nullptr;

	static const float TravelDistance;
};
