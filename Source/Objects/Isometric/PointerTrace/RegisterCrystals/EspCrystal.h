#pragma once

#include "Objects/Isometric/PointerTrace/RegisterCrystals/RegisterCrystal.h"

namespace cocos2d
{
	class Sprite;
}

class EspCrystal : public RegisterCrystal
{
public:
	static EspCrystal* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyEspCrystal;

protected:
	EspCrystal(cocos2d::ValueMap& initProperties);
	~EspCrystal();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef RegisterCrystal super;

	cocos2d::Sprite* crystal;
};
