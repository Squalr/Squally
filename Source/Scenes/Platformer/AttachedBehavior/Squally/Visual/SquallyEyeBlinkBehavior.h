#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;
class SmartAnimationSequenceNode;

class SquallyEyeBlinkBehavior : public AttachedBehavior
{
public:
	static SquallyEyeBlinkBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyEyeBlinkBehavior(GameObject* owner);
	~SquallyEyeBlinkBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;
	
	void runEyeBlinkLoop();

	SmartAnimationSequenceNode* leftEyeController;
	SmartAnimationSequenceNode* rightEyeController;

	Squally* squally;
};
