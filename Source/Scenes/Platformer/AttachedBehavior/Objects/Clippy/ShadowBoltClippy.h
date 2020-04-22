#pragma once
#include <set>

#include "Engine/Hackables/Menus/Clippy.h"

class SmartAnimationNode;

class ShadowBoltClippy : public Clippy
{
public:
	static ShadowBoltClippy* create();

	void startDialogue() override;

protected:
	ShadowBoltClippy();
	virtual ~ShadowBoltClippy();

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
