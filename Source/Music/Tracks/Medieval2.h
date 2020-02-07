#pragma once

#include "Engine/Sound/Track.h"

class Item;

class Medieval2 : public Track
{
public:
	static Medieval2* create();

	static const std::string TrackKey;

protected:
	Medieval2();
	virtual ~Medieval2();

private:
	typedef Track super;
};
