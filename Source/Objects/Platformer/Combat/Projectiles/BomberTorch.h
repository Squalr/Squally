#pragma once

#include "Engine/Physics/ProximityObject.h"

namespace cocos2d
{
	class Sprite;
}

class BomberTorch : public ProximityObject
{
public:
	static BomberTorch* create();

protected:
	BomberTorch();
	virtual	~BomberTorch();

private:
	typedef ProximityObject super;

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;

	cocos2d::Sprite* bomberTorchSprite;
};
