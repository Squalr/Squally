#pragma once
#include <set>

#include "Engine/Hackables/Menus/Clippy.h"

class SmartAnimationNode;

class IsSwimmingClippy : public Clippy
{
public:
	static IsSwimmingClippy* create();

	void startDialogue() override;

protected:
	IsSwimmingClippy();
	virtual ~IsSwimmingClippy();

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
