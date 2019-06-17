#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;
class Sound;

class WindClippy : public Clippy
{
public:
	static WindClippy* create();

protected:
	WindClippy();
	~WindClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	void onEnterTransitionDidFinish() override;

	SmartAnimationNode* clippyAnimations;
	Sound* droidChatterSound;
};
