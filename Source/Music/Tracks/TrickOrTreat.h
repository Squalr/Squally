#pragma once

#include "Engine/Sound/Track.h"

class Item;

class TrickOrTreat : public Track
{
public:
	static TrickOrTreat* create();

	static const std::string TrackKey;

protected:
	TrickOrTreat();
	virtual ~TrickOrTreat();

private:
	typedef Track super;
};
