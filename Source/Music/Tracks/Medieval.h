#pragma once

#include "Engine/Sound/Track.h"

class Item;

class Medieval : public Track
{
public:
	static Medieval* create();

	static const std::string TrackKey;

protected:
	Medieval();
	virtual ~Medieval();

private:
	typedef Track super;
};
