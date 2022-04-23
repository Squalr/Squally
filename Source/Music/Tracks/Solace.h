#pragma once

#include "Engine/Sound/Music.h"

class Solace : public Music
{
public:
	static Solace* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	Solace(cocos2d::ValueMap& properties);
	virtual ~Solace();

private:
	typedef Music super;
};
