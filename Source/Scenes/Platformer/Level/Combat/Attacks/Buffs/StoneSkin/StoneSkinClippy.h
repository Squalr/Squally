#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;
class Sound;

class StoneSkinClippy : public Clippy
{
public:
	static StoneSkinClippy* create();

	void startDialogue() override;

protected:
	StoneSkinClippy();
	virtual ~StoneSkinClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
