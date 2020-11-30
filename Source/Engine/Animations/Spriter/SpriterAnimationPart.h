#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/SmartNode.h"

class SpriterAnimationPart : public SmartNode
{
public:
	static SpriterAnimationPart* create();

protected:
	SpriterAnimationPart();
	virtual ~SpriterAnimationPart();

private:
	typedef SmartNode super;
};
