#pragma once
#include <set>

#include "Engine/Hackables/Menus/Clippy.h"

class SmartAnimationNode;

class IsAliveClippy : public Clippy
{
public:
	static IsAliveClippy* create();

	void startDialogue() override;

protected:
	IsAliveClippy();
	virtual ~IsAliveClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
