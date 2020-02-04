#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;

class SpeedGainClippy : public Clippy
{
public:
	static SpeedGainClippy* create();

protected:
	SpeedGainClippy();
	virtual ~SpeedGainClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	void onEnterTransitionDidFinish() override;

	SmartAnimationNode* clippyAnimations;
};
