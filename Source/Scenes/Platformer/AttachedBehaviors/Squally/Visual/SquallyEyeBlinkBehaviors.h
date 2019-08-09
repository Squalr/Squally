#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;
class SmartAnimationSequenceNode;

class SquallyEyeBlinkBehaviors : public AttachedBehavior
{
public:
	static SquallyEyeBlinkBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyEyeBlinkBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyEyeBlinkBehaviors();

	void onLoad() override;

private:
	typedef AttachedBehavior super;
	
	void runEyeBlinkLoop();

	SmartAnimationSequenceNode* leftEyeController;
	SmartAnimationSequenceNode* rightEyeController;

	Squally* squally;
};
