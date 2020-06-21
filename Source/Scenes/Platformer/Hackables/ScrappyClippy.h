#pragma once
#include <set>

#include "Engine/Hackables/Menus/Clippy.h"

class LocalizedString;
class SmartAnimationNode;
class Sound;

class ScrappyClippy : public Clippy
{
public:
	static ScrappyClippy* create(LocalizedString* helpText, std::string uniqueRunKey = "");

	void startDialogue() override;

protected:
	ScrappyClippy(LocalizedString* helpText, std::string uniqueRunKey);
	virtual ~ScrappyClippy();

private:
	typedef Clippy super;

	SmartAnimationNode* clippyAnimations;
	LocalizedString* helpText;
};
