#pragma once
#include "Engine/SmartNode.h"

class SmartAnimationSequenceNode;

class Smoke : public SmartNode
{
public:
	static Smoke* create(SmartNode* followTarget);

	void stopFollow();

private:
	Smoke(SmartNode* followTarget);
	~Smoke();

	void onEnter() override;

	SmartNode* follow;
	SmartAnimationSequenceNode* smokeAnimation;

	static const std::string ScheduleKeySpawnSmoke;
};
