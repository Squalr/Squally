#pragma once

#include "Objects/Platformer/Interactables/Doors/Mayan/MayanRuneBase.h"

class MayanGemPurple : public MayanRuneBase
{
public:
	static MayanGemPurple* create();

	int runGem(int currentIndex) override;

protected:
	MayanGemPurple();
	virtual ~MayanGemPurple();
	
	void registerHackables() override;

private:
	typedef MayanRuneBase super;

	int runGemPurple(int currentIndex);
};
