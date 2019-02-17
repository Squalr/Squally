#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class BomberTorchGenericPreview : public HackablePreview
{
public:
	static BomberTorchGenericPreview* create();

	HackablePreview* clone() override;

protected:
	BomberTorchGenericPreview();
	virtual ~BomberTorchGenericPreview();
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* bomberTorch;
};
