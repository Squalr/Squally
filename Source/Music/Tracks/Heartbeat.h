#pragma once

#include "Engine/Sound/Music.h"

class Heartbeat : public Music
{
public:
	static Heartbeat* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	Heartbeat(cocos2d::ValueMap& properties);
	virtual ~Heartbeat();

private:
	typedef Music super;
};
