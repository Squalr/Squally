#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerColor;
}

class Explosion : public SmartNode
{
public:
	static Explosion* create();

private:
	Explosion();
	~Explosion();

	void onEnter() override;

	cocos2d::LayerColor* explosion;
};
