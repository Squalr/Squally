#include "TwoSteps.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TwoSteps::TrackKey = "two-steps";

TwoSteps* TwoSteps::create(cocos2d::ValueMap& properties)
{
	TwoSteps* instance = new TwoSteps(properties);

	instance->autorelease();

	return instance;
}

TwoSteps::TwoSteps(cocos2d::ValueMap& properties) : super(properties, MusicResources::Two_Steps, Strings::Menus_Music_StrayGhost_TwoSteps::create(), Strings::Menus_Music_StrayGhost_StrayGhost::create())
{
}

TwoSteps::~TwoSteps()
{
}
