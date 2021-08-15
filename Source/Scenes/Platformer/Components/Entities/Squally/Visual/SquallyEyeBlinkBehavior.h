#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;
class SmartAnimationSequenceNode;

class SquallyEyeBlinkBehavior : public GameComponent
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
	typedef GameComponent super;
	
	void runEyeBlinkLoop();

	SmartAnimationSequenceNode* leftEyeController = nullptr;
	SmartAnimationSequenceNode* rightEyeController = nullptr;
	Squally* squally = nullptr;
};
