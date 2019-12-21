#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;

class IsAliveClippy : public Clippy
{
public:
	static IsAliveClippy* create();

protected:
	IsAliveClippy();
	~IsAliveClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	void onEnterTransitionDidFinish() override;

	SmartAnimationNode* clippyAnimations;
};
