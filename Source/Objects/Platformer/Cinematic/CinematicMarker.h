#pragma once

#include "Engine/Hackables/HackableObject.h"

class CollisionObject;
class HackableData;

class CinematicMarker : public HackableObject
{
public:
	static CinematicMarker* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CinematicMarker(cocos2d::ValueMap& properties);
	virtual ~CinematicMarker();

private:
	typedef HackableObject super;
};
