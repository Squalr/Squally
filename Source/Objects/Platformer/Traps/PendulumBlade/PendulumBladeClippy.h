#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;
class Sound;

class PendulumBladeClippy : public Clippy
{
public:
	static PendulumBladeClippy* create();

	Clippy* clone() override;

protected:
	PendulumBladeClippy();
	~PendulumBladeClippy();

private:
	typedef Clippy super;

	void onEnterTransitionDidFinish() override;

	SmartAnimationNode* clippyAnimations;
	Sound* droidChatterSound;
};
