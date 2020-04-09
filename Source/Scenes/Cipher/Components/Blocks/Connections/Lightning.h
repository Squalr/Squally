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

protected:
	Lightning();
	virtual ~Lightning();

	void onEnter() override;

private:
	typedef SmartNode super;
	
	void playAnimationsInternal(bool repeat, bool isFirstRun = false);

	SmartAnimationSequenceNode* animations;
	Sound* sound;
	float manualDelay;
};
