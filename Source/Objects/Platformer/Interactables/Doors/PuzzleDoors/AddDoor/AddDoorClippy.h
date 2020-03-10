#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;

class AddDoorClippy : public Clippy
{
public:
	static AddDoorClippy* create();

protected:
	AddDoorClippy();
	virtual ~AddDoorClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	void onEnterTransitionDidFinish() override;

	SmartAnimationNode* clippyAnimations;
};
