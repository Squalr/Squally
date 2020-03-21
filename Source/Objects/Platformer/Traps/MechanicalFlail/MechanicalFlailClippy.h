#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;
class Sound;

class MechanicalFlailClippy : public Clippy
{
public:
	static MechanicalFlailClippy* create();

	void startDialogue() override;

protected:
	MechanicalFlailClippy();
	virtual ~MechanicalFlailClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
