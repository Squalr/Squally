#pragma once

#include "Objects/Isometric/PointerTrace/RegisterCrystals/RegisterCrystal.h"

namespace cocos2d
{
	class Sprite;
}

class EaxCrystal : public RegisterCrystal
{
public:
	static EaxCrystal* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	EaxCrystal(cocos2d::ValueMap& properties);
	virtual ~EaxCrystal();

	void onEnter() override;
	void initializePositions() override;
	void updateRegister(int value) override;
	int getRegisterValue() override;

private:
	typedef RegisterCrystal super;

	cocos2d::Sprite* crystal;
};
