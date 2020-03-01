#pragma once

#include "Objects/Platformer/Interactables/Doors/Mayan/MayanRuneBase.h"

class MayanGemPurple : public MayanRuneBase
{
public:
	static MayanGemPurple* create();

	static const std::string MapKeyMayanGemPurple;
	static const std::string RedGemEvent;

protected:
	MayanGemPurple();
	virtual ~MayanGemPurple();

private:
	typedef MayanRuneBase super;
};
