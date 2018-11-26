#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

#include "Engine/SmartNode.h"

using namespace cocos2d;

class SmartAnimationNode : public SmartNode
{
public:
	static SmartAnimationNode* create(std::string animationResource);
	static SmartAnimationNode* create(std::string animationResource, std::string entityName);

	void playAnimation(float blendTime = 0.25f);
	void playAnimation(std::string animationName, float blendTime = 0.25f);

	static const std::string DefaultAnimationEntityName;
	static const std::string DefaultAnimationName;

protected:
	AnimationNode* animationNode;
	SpriterEngine::EntityInstance* entity;

private:
	SmartAnimationNode(std::string animationResource, std::string entityName);
	~SmartAnimationNode();
};
