#pragma once

#include "Objects/Platformer/Interactables/Doors/Mayan/MayanRuneBase.h"

class MayanGemBlue : public MayanRuneBase
{
public:
	static MayanGemBlue* create();

protected:
	MayanGemBlue();
	virtual ~MayanGemBlue();

private:
	typedef MayanRuneBase super;
};
