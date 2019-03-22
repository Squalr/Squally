#pragma once

#include "Engine/SmartNode.h"

class SmartAnimationSequenceNode;

class Lightning : public SmartNode
{
public:
	static Lightning* create();

	void setManualDelay(float manualDelay);
	void setLightningCallback(std::function<void()> onLightningCallback);

private:
	typedef SmartNode super;
	Lightning();
	~Lightning();

	void onEnter() override;
	void playNextAnimation();

	SmartAnimationSequenceNode* animations;
	bool firstRun;
	float manualDelay;
	std::function<void()> onLightningCallback;
};

