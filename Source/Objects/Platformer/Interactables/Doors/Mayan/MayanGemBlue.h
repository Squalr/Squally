#pragma once

#include "Objects/Platformer/Interactables/Doors/Mayan/MayanRuneBase.h"

class MayanGemBlue : public MayanRuneBase
{
public:
	static MayanGemBlue* create();

	int runGem(int currentIndex) override;

protected:
	MayanGemBlue();
	virtual ~MayanGemBlue();
	
	void registerHackables() override;

private:
	typedef MayanRuneBase super;

	int runGemBlue(int currentIndex);
};
