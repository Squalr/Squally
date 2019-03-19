#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class Bolt : public SmartNode
{
public:
	static Bolt* create(bool isInput);

private:
	typedef SmartNode super;
	Bolt(bool isInput);
	~Bolt();

	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* bolt;
};
