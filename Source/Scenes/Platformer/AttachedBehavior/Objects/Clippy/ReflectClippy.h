#pragma once
#include <set>

#include "Engine/Hackables/Menus/Clippy.h"

class SmartAnimationNode;
class Sound;

class ReflectClippy : public Clippy
{
public:
	static ReflectClippy* create();

	void startDialogue() override;

protected:
	ReflectClippy();
	virtual ~ReflectClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
