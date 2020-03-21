#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;

class MulDoorClippy : public Clippy
{
public:
	static MulDoorClippy* create();

	void startDialogue() override;

protected:
	MulDoorClippy();
	virtual ~MulDoorClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
