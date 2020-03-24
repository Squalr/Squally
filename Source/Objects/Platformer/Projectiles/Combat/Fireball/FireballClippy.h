#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;

class FireballClippy : public Clippy
{
public:
	static FireballClippy* create();

	void startDialogue() override;

protected:
	FireballClippy();
	virtual ~FireballClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
