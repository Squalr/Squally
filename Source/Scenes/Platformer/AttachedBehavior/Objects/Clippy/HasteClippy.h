#pragma once
#include <set>

#include "Engine/Hackables/Menus/Clippy.h"

class SmartAnimationNode;
class Sound;

class HasteClippy : public Clippy
{
public:
	static HasteClippy* create();

	void startDialogue() override;

protected:
	HasteClippy();
	virtual ~HasteClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
