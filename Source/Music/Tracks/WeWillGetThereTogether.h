#pragma once

#include "Engine/Sound/Music.h"

class WeWillGetThereTogether : public Music
{
public:
	static WeWillGetThereTogether* create();

	static const std::string TrackKey;

protected:
	WeWillGetThereTogether();
	virtual ~WeWillGetThereTogether();

private:
	typedef Music super;
};
