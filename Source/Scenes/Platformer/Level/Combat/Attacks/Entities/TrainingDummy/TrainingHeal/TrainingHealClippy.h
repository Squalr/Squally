#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;
class Sound;

class TrainingHealClippy : public Clippy
{
public:
	static TrainingHealClippy* create();

protected:
	TrainingHealClippy();
	virtual ~TrainingHealClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	void onEnterTransitionDidFinish() override;

	SmartAnimationNode* clippyAnimations;
};
