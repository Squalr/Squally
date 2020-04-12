#pragma once
#include <set>

#include "Engine/Hackables/Menus/Clippy.h"

class SmartAnimationNode;
class Sound;

class EnrageClippy : public Clippy
{
public:
	static EnrageClippy* create();

	void startDialogue() override;

protected:
	EnrageClippy();
	virtual ~EnrageClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
