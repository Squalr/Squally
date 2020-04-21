#pragma once
#include <set>

#include "Engine/Hackables/Menus/Clippy.h"

class SmartAnimationNode;
class Sound;

class PendulumBladeClippy : public Clippy
{
public:
	static PendulumBladeClippy* create();

	void startDialogue() override;

protected:
	PendulumBladeClippy();
	virtual ~PendulumBladeClippy();

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
