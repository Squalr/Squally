#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/SmartNode.h"

class SpriterAnimationPart : public SmartNode
{
public:
	int getId() const;

protected:
	SpriterAnimationPart();
	virtual ~SpriterAnimationPart();

private:
	typedef SmartNode super;
};
