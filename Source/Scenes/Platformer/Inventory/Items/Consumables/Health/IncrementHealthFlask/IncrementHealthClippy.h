#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;
class Sound;

class IncrementHealthClippy : public Clippy
{
public:
	static IncrementHealthClippy* create();

protected:
	IncrementHealthClippy();
	virtual ~IncrementHealthClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	void onEnterTransitionDidFinish() override;

	SmartAnimationNode* clippyAnimations;
};
