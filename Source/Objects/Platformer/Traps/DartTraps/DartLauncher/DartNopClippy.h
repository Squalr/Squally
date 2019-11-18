#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;

class DartNopClippy : public Clippy
{
public:
	static DartNopClippy* create();

protected:
	DartNopClippy();
	~DartNopClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	void onEnterTransitionDidFinish() override;

	SmartAnimationNode* clippyAnimations;
};
