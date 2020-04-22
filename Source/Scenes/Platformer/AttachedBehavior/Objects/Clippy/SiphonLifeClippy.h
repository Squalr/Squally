#pragma once
#include <set>

#include "Engine/Hackables/Menus/Clippy.h"

class SmartAnimationNode;
class Sound;

class SiphonLifeClippy : public Clippy
{
public:
	static SiphonLifeClippy* create();

	void startDialogue() override;

protected:
	SiphonLifeClippy();
	virtual ~SiphonLifeClippy();

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
