#pragma once
#include "Engine/SmartNode.h"

class SpriterAnimation : public SmartNode
{
public:
	static AnimationPart* create(std::string animationResource);

private:
	typedef SmartNode super;
	SpriterAnimation(std::string animationResource);

	stuct Bone
	{
		cocos2d::Vec2 size;
		cocos2d::Vec2 position;
		cocos2d::Vec2 scale;
		float angle;
	};
};
