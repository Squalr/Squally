#pragma once
#include <set>

#include "Engine/Hackables/Menus/Clippy.h"

class SmartAnimationNode;
class Sound;

class TrainingHealClippy : public Clippy
{
public:
	static TrainingHealClippy* create();

	void startDialogue() override;

protected:
	TrainingHealClippy();
	virtual ~TrainingHealClippy();

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
