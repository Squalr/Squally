#pragma once

#include "Objects/Platformer/Interactables/Doors/Mayan/MayanRuneBase.h"

class MayanGemPurple : public MayanRuneBase
{
public:
	static MayanGemPurple* create();

protected:
	MayanGemPurple();
	virtual ~MayanGemPurple();

private:
	typedef MayanRuneBase super;
};
