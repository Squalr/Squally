#pragma once

#include "Objects/Platformer/Interactables/Doors/Mayan/MayanRuneBase.h"

class MayanGemRed : public MayanRuneBase
{
public:
	static MayanGemRed* create();

	static const std::string MapKeyMayanGemRed;
	static const std::string RedGemEvent;

protected:
	MayanGemRed();
	virtual ~MayanGemRed();

private:
	typedef MayanRuneBase super;
};
