#pragma once

#include "Objects/Platformer/Interactables/Doors/Mayan/MayanRuneBase.h"

class MayanGemBlue : public MayanRuneBase
{
public:
	static MayanGemBlue* create();

	static const std::string MapKeyMayanGemBlue;
	static const std::string RedGemEvent;

protected:
	MayanGemBlue();
	virtual ~MayanGemBlue();

private:
	typedef MayanRuneBase super;
};
