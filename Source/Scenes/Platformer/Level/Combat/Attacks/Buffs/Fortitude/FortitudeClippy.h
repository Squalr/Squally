#pragma once
#include <set>

#include "Engine/Hackables/Menus/Clippy.h"

class SmartAnimationNode;
class Sound;

class FortitudeClippy : public Clippy
{
public:
	static FortitudeClippy* create();

	void startDialogue() override;

protected:
	FortitudeClippy();
	virtual ~FortitudeClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
