#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;

class IsSwimmingClippy : public Clippy
{
public:
	static IsSwimmingClippy* create();

	void startDialogue() override;

protected:
	IsSwimmingClippy();
	virtual ~IsSwimmingClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
