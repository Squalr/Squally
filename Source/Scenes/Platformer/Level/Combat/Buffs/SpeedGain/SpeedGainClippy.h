#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;
class Sound;

class SpeedGainClippy : public Clippy
{
public:
	static SpeedGainClippy* create();

protected:
	SpeedGainClippy();
	~SpeedGainClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	void onEnterTransitionDidFinish() override;

	SmartAnimationNode* clippyAnimations;
	Sound* droidChatterSound;
};
