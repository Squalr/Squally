#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;
class Sound;

class LesserStrengthClippy : public Clippy
{
public:
	static LesserStrengthClippy* create();

	void startDialogue() override;

protected:
	LesserStrengthClippy();
	virtual ~LesserStrengthClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
