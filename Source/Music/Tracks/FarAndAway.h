#pragma once

#include "Engine/Sound/Music.h"

class FarAndAway : public Music
{
public:
	static FarAndAway* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	FarAndAway(cocos2d::ValueMap& properties);
	virtual ~FarAndAway();

private:
	typedef Music super;
};
