#pragma once

#include "Engine/Sound/Track.h"

class Item;

class Solace : public Track
{
public:
	static Solace* create();

	static const std::string TrackKey;

protected:
	Solace();
	virtual ~Solace();

private:
	typedef Track super;
};
