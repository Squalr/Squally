#pragma once

#include "Engine/Sound/Music.h"

class Heartbeat : public Music
{
public:
	static Heartbeat* create();

	static const std::string TrackKey;

protected:
	Heartbeat();
	virtual ~Heartbeat();

private:
	typedef Music super;
};
