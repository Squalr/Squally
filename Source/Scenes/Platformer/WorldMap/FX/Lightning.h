#pragma once

#include "Engine/SmartNode.h"

class SmartAnimationSequenceNode;
class Sound;

class Lightning : public SmartNode
{
public:
	static Lightning* create();

	void playAnimations(bool repeat = true);
	void setManualDelay(float manualDelay);

private:
	typedef SmartNode super;
	Lightning();
	~Lightning();

	void onEnter() override;
	void playAnimationsInternal(bool repeat, bool isFirstRun = false);

	SmartAnimationSequenceNode* animations;
	Sound* sound;
	float manualDelay;
};

