#pragma once
#include <set>

#include "Engine/Hackables/Menus/Clippy.h"

class SmartAnimationNode;

class DartNopClippy : public Clippy
{
public:
	static DartNopClippy* create();

	void startDialogue() override;

protected:
	DartNopClippy();
	virtual ~DartNopClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
