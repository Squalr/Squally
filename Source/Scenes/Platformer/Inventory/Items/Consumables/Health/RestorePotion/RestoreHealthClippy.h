#pragma once
#include <set>

#include "Engine/Hackables/Clippy.h"

class SmartAnimationNode;
class Sound;

class RestoreHealthClippy : public Clippy
{
public:
	static RestoreHealthClippy* create();

protected:
	RestoreHealthClippy();
	~RestoreHealthClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	void onEnterTransitionDidFinish() override;

	SmartAnimationNode* clippyAnimations;
};
