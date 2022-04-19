#pragma once

#include "Engine/Sound/Music.h"

class Solace : public Music
{
public:
	static Solace* create();

	static const std::string TrackKey;

protected:
	Solace();
	virtual ~Solace();

private:
	typedef Music super;
};
