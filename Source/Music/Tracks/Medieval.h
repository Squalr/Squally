#pragma once

#include "Engine/Sound/Music.h"

class Medieval : public Music
{
public:
	static Medieval* create();

	static const std::string TrackKey;

protected:
	Medieval();
	virtual ~Medieval();

private:
	typedef Music super;
};
