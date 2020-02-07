#pragma once

#include "Engine/SmartNode.h"

class Music;

// Wrapper object for music, as music objects behave a little irregularly due to their global nature.
class Track : public SmartNode
{
public:
	virtual void push(float delay = 0.0f);
	virtual void play(float delay = 0.0f);
	virtual void pop();

protected:
	Track(std::string musicResource);
	virtual ~Track();

private:
	typedef SmartNode super;

	bool isParentGlobal();

	Music* music;
};
