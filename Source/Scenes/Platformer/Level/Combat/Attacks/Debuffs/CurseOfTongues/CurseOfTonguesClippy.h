#pragma once
#include <set>

#include "Engine/Hackables/Menus/Clippy.h"

class SmartAnimationNode;
class Sound;

class CurseOfTonguesClippy : public Clippy
{
public:
	static CurseOfTonguesClippy* create();

	void startDialogue() override;

protected:
	CurseOfTonguesClippy();
	virtual ~CurseOfTonguesClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
};
