#pragma once
#include <set>

#include "Engine/Hackables/Menus/Clippy.h"

class SmartAnimationNode;
class Sound;

class BlindClippy : public Clippy
{
public:
	static BlindClippy* create();

	void startDialogue() override;

protected:
	BlindClippy();
	virtual ~BlindClippy();

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
