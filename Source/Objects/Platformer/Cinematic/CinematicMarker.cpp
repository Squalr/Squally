#include "CinematicMarker.h"

using namespace cocos2d;

const std::string CinematicMarker::MapKey = "cinematic-marker";

CinematicMarker* CinematicMarker::create(ValueMap& properties)
{
	CinematicMarker* instance = new CinematicMarker(properties);

	instance->autorelease();

	return instance;
}

CinematicMarker::CinematicMarker(ValueMap& properties) : super(properties)
{
}

CinematicMarker::~CinematicMarker()
{
}
