#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/SmartNode.h"

class SpriterAnimationNode : public SmartNode
{
public:
	static SpriterAnimationNode* create(std::string animationResource);

protected:
	SpriterAnimationNode(std::string animationResource);

private:
	typedef SmartNode super;
};
