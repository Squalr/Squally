#pragma once
#include <set>

#include "Engine/Hackables/Menus/Clippy.h"

class SmartAnimationNode;

class WindClippy : public Clippy
{
public:
	static WindClippy* create();

	void startDialogue() override;

protected:
	WindClippy();
	virtual ~WindClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
