#pragma once

#include "Engine/Components/Component.h"

class Squally;
class SmartAnimationSequenceNode;

class SquallyEyeBlinkBehavior : public Component
{
public:
	static SquallyEyeBlinkBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyEyeBlinkBehavior(GameObject* owner);
	virtual ~SquallyEyeBlinkBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;
	
	void runEyeBlinkLoop();

	SmartAnimationSequenceNode* leftEyeController;
	SmartAnimationSequenceNode* rightEyeController;

	Squally* squally;
};
