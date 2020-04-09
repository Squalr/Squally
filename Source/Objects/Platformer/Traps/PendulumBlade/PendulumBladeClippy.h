#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

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

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
