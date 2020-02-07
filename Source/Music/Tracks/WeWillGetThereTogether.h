#pragma once

#include "Engine/Sound/Track.h"

class Item;

class WeWillGetThereTogether : public Track
{
public:
	static WeWillGetThereTogether* create(SmartNode* owner);

	static const std::string TrackKey;

protected:
	WeWillGetThereTogether(SmartNode* owner);
	virtual ~WeWillGetThereTogether();

private:
	typedef Track super;
};
