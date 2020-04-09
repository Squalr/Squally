#pragma once

#include "Objects/Platformer/Interactables/Doors/Mayan/MayanRuneBase.h"

class MayanGemRed : public MayanRuneBase
{
public:
	static MayanGemRed* create();

protected:
	MayanGemRed();
	virtual ~MayanGemRed();

	cocos2d::Color4B getGemFontColor() override;

private:
	typedef MayanRuneBase super;

	int runGemRed(int currentIndex);
};
