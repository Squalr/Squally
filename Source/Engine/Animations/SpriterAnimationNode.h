#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class SpriterAnimationNode : public SmartNode
{
public:
	static SpriterAnimationNode* create(std::string animationResource);

protected:
	SpriterAnimationNode(std::string animationResource);

private:
	typedef SmartNode super;

	std::vector<cocos2d::Sprite*> animationParts;

	void loadAnimationData(std::string animationResource);
	
	cocos2d::Node* animationPartContainer;
};
