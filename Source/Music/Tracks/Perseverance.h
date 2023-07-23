#pragma once

#include "Engine/Sound/Music.h"

class Perseverance : public Music
{
public:
	static Perseverance* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	Perseverance(cocos2d::ValueMap& properties);
	virtual ~Perseverance();

private:
	typedef Music super;
};
