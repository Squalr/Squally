#pragma once

#include "Engine/Sound/Track.h"

class Item;

class Heartbeat : public Track
{
public:
	static Heartbeat* create(SmartNode* owner);

	static const std::string TrackKey;

protected:
	Heartbeat(SmartNode* owner);
	virtual ~Heartbeat();

private:
	typedef Track super;
};
