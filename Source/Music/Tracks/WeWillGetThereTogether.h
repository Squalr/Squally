#pragma once

#include "Engine/Sound/Track.h"

class Item;

class WeWillGetThereTogether : public Track
{
public:
	static WeWillGetThereTogether* create();

	static const std::string TrackKey;

protected:
	WeWillGetThereTogether();
	virtual ~WeWillGetThereTogether();

private:
	typedef Track super;
};
