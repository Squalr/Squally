#pragma once

#include "Objects/Platformer/Interactables/Doors/Mayan/MayanRuneBase.h"

class MayanGemRed : public MayanRuneBase
{
public:
	static MayanGemRed* create();

	int runGem(int currentIndex) override;

protected:
	MayanGemRed();
	virtual ~MayanGemRed();
	
	void registerHackables() override;

private:
	typedef MayanRuneBase super;

	int runGemRed(int currentIndex);
};
