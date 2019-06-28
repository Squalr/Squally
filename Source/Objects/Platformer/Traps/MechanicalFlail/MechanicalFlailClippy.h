#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;
class Sound;

class MechanicalFlailClippy : public Clippy
{
public:
	static MechanicalFlailClippy* create();

protected:
	MechanicalFlailClippy();
	~MechanicalFlailClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	void onEnterTransitionDidFinish() override;

	SmartAnimationNode* clippyAnimations;
	Sound* droidChatterSound;
};
