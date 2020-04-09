#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;

class ShadowBoltClippy : public Clippy
{
public:
	static ShadowBoltClippy* create();

	void startDialogue() override;

protected:
	ShadowBoltClippy();
	virtual ~ShadowBoltClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
