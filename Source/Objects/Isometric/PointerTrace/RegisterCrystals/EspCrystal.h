#pragma once

#include "Objects/Isometric/PointerTrace/RegisterCrystals/RegisterCrystal.h"

namespace cocos2d
{
	class Sprite;
}

class EspCrystal : public RegisterCrystal
{
public:
	static EspCrystal* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyEspCrystal;

protected:
	EspCrystal(cocos2d::ValueMap& properties);
	~EspCrystal();

	void onEnter() override;
	void initializePositions() override;
	void updateRegister(int value) override;
	int getRegisterValue() override;

private:
	typedef RegisterCrystal super;

	cocos2d::Sprite* crystal;
};
