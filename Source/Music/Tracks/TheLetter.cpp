#include "TheLetter.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TheLetter::TrackKey = "the-letter";

TheLetter* TheLetter::create(cocos2d::ValueMap& properties)
{
	TheLetter* instance = new TheLetter(properties);

	instance->autorelease();

	return instance;
}

TheLetter::TheLetter(cocos2d::ValueMap& properties) : super(properties, MusicResources::TheLetter, Strings::TODO::create(), Strings::TODO::create())
{
}

TheLetter::~TheLetter()
{
}
