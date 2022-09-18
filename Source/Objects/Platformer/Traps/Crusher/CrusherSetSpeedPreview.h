#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

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

private:
	typedef HackablePreview super;

	cocos2d::Sprite* previewCrusher100 = nullptr;
	cocos2d::Sprite* previewCrusher200 = nullptr;
	cocos2d::Sprite* previewCrusher400 = nullptr;
	LocalizedLabel* eax100Height = nullptr;
	LocalizedLabel* eax200Height = nullptr;
	LocalizedLabel* eax400Height = nullptr;
};
