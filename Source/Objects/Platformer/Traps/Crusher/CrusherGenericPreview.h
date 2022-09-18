#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

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

	cocos2d::Sprite* previewCrusher = nullptr;
};
