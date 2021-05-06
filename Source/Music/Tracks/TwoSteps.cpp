#include "TwoSteps.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TwoSteps::TrackKey = "two-steps";

TwoSteps* TwoSteps::create()
{
	TwoSteps* instance = new TwoSteps();

	instance->autorelease();

	return instance;
}

TwoSteps::TwoSteps() : super(MusicResources::TwoStepsTooOftenAside, Strings::Menus_Music_StrayGhost_TwoStepsTooOftenAside::create(), Strings::Menus_Music_StrayGhost_StrayGhost::create())
{
}

TwoSteps::~TwoSteps()
{
}
