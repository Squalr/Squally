#pragma once

#include "Engine/Sound/Music.h"

class RacingAgainstTheSunset : public Music
{
public:
	static RacingAgainstTheSunset* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	RacingAgainstTheSunset(cocos2d::ValueMap& properties);
	virtual ~RacingAgainstTheSunset();

private:
	typedef Music super;
};
