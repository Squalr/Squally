#pragma once

#include "Engine/Sound/Music.h"

class TrickOrTreat : public Music
{
public:
	static TrickOrTreat* create();

	static const std::string TrackKey;

protected:
	TrickOrTreat();
	virtual ~TrickOrTreat();

private:
	typedef Music super;
};
