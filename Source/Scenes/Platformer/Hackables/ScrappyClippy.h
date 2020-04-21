#pragma once
#include <set>

#include "Engine/Hackables/Menus/Clippy.h"

class LocalizedString;
class SmartAnimationNode;
class Sound;

class ScrappyClippy : public Clippy
{
public:
	static ScrappyClippy* create(LocalizedString* helpText);

	void startDialogue() override;

protected:
	ScrappyClippy(LocalizedString* helpText);
	virtual ~ScrappyClippy();

	Clippy* innerClone() override;

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
	LocalizedString* helpText;
};
