#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;
class Sound;

class WindClippy : public Clippy
{
public:
	static WindClippy* create();

	Clippy* clone() override;

protected:
	WindClippy();
	~WindClippy();

private:
	typedef Clippy super;

	void onEnterTransitionDidFinish() override;

	SmartAnimationNode* clippyAnimations;
	Sound* droidChatterSound;
};
