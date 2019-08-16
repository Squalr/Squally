#pragma once

#include "Objects/Isometric/PointerTrace/RegisterCrystals/RegisterCrystal.h"

namespace cocos2d
{
	class Sprite;
}

class EsiCrystal : public RegisterCrystal
{
public:
	static EsiCrystal* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyEsiCrystal;

protected:
	EsiCrystal(cocos2d::ValueMap& properties);
	~EsiCrystal();

	void onEnter() override;
	void initializePositions() override;
	void updateRegister(int value) override;
	int getRegisterValue() override;

private:
	typedef RegisterCrystal super;

	cocos2d::Sprite* crystal;
};
