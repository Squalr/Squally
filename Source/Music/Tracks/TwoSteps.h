#pragma once

#include "Engine/Sound/Track.h"

class TwoSteps : public Track
{
public:
	static TwoSteps* create();

	static const std::string TrackKey;

protected:
	TwoSteps();
	virtual ~TwoSteps();

private:
	typedef Track super;
};
