#include "SpriterAnimationNode.h"

#include "cocos/platform/CCFileUtils.h"

#include "Engine/Animations/SpriterAnimationParser.h"

using namespace cocos2d;

SpriterAnimationNode* SpriterAnimationNode::create(std::string animationResource)
{
	SpriterAnimationNode* instance = new SpriterAnimationNode(animationResource);

	instance->autorelease();

	return instance;
}

SpriterAnimationNode::SpriterAnimationNode(std::string animationResource)
{
	SpriterData spriterData = SpriterAnimationParser::Parse(animationResource);
}
