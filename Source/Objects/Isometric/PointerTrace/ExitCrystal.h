#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

namespace cocos2d
{
	class Sprite;
}

class ExitCrystal : public GridObject
{
public:
	static ExitCrystal* create(cocos2d::ValueMap& initProperties);

	int getValue();
	int getOffset();

	static const std::string MapKeyExitCrystal;

protected:
	ExitCrystal(cocos2d::ValueMap& initProperties);
	~ExitCrystal();

	void onEnter() override;
	void initializePositions() override;


private:
	typedef GridObject super;

	cocos2d::Sprite* crystal;
	cocos2d::Sprite* shadow;
};
