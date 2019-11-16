#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;
class Sound;

class PendulumBladeClippy : public Clippy
{
public:
	static PendulumBladeClippy* create();

protected:
	PendulumBladeClippy();
	~PendulumBladeClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	void onEnterTransitionDidFinish() override;

	SmartAnimationNode* clippyAnimations;
};
