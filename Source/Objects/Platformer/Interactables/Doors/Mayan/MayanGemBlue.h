#pragma once

#include "Objects/Platformer/Interactables/Doors/Mayan/MayanRuneBase.h"

class MayanGemBlue : public MayanRuneBase
{
public:
	static MayanGemBlue* create();

protected:
	MayanGemBlue();
	virtual ~MayanGemBlue();

	cocos2d::Color4B getGemFontColor() override;

private:
	typedef MayanRuneBase super;
};
