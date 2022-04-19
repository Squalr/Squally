#pragma once

#include "Engine/Sound/Music.h"

class Medieval2 : public Music
{
public:
	static Medieval2* create();

	static const std::string TrackKey;

protected:
	Medieval2();
	virtual ~Medieval2();

private:
	typedef Music super;
};
