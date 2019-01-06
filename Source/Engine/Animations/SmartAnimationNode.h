#pragma once
#include "Engine/SmartNode.h"

// forward declarations
namespace cocos2d
{
	class AnimationNode;
}

namespace SpriterEngine
{
	class EntityInstance;
}

class SmartAnimationNode : public SmartNode
{
public:
	static SmartAnimationNode* create(std::string animationResource);
	static SmartAnimationNode* create(std::string animationResource, std::string entityName);

	struct AnimationPart
	{
		float rotation;

		AnimationPart() : rotation(0.0f) { }
		AnimationPart(float rotation) : rotation(rotation) { }
	};

	void playAnimation(bool repeat = false, float blendTime = 0.25f);
	void playAnimation(const char* animationName, bool repeat = false, float blendTime = 0.25f);
	void playAnimation(std::string animationName, bool repeat = false, float blendTime = 0.25f);
	AnimationPart getAnimationPart(std::string partName);
	void setAnimationPart(std::string partName, AnimationPart animationPart);
	void restoreAnimationPart(std::string partName);
	void setFlippedX(bool flippedX);
	void setFlippedY(bool flippedY);

	static const std::string DefaultAnimationEntityName;
	static const std::string DefaultAnimationName;

protected:
	cocos2d::AnimationNode* animationNode;
	SpriterEngine::EntityInstance* entity;

private:
	typedef SmartNode super;
	SmartAnimationNode(std::string animationResource, std::string entityName);
	virtual ~SmartAnimationNode();
};
