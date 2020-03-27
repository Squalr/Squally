#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;

class TimeBombClippy : public Clippy
{
public:
	static TimeBombClippy* create();

	void startDialogue() override;

protected:
	TimeBombClippy();
	virtual ~TimeBombClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
