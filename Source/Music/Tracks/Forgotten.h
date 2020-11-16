#pragma once

#include "Engine/Sound/Track.h"

class Forgotten : public Track
{
public:
	static Forgotten* create();

	static const std::string TrackKey;

protected:
	Forgotten();
	virtual ~Forgotten();

private:
	typedef Track super;
};
