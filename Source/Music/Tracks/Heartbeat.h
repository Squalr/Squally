#pragma once

#include "Engine/Sound/Track.h"

class Heartbeat : public Track
{
public:
	static Heartbeat* create();

	static const std::string TrackKey;

protected:
	Heartbeat();
	virtual ~Heartbeat();

private:
	typedef Track super;
};
