#pragma once

#include "Engine/Sound/Music.h"

class RaceAgainstTheSunset : public Music
{
public:
	static RaceAgainstTheSunset* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	RaceAgainstTheSunset(cocos2d::ValueMap& properties);
	virtual ~RaceAgainstTheSunset();

private:
	typedef Music super;
};
