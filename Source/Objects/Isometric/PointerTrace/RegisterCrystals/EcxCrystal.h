#pragma once

#include "Objects/Isometric/PointerTrace/RegisterCrystals/RegisterCrystal.h"

namespace cocos2d
{
	class Sprite;
}

class EcxCrystal : public RegisterCrystal
{
public:
	static EcxCrystal* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyEcxCrystal;

protected:
	EcxCrystal(cocos2d::ValueMap& properties);
	~EcxCrystal();

	void onEnter() override;
	void initializePositions() override;
	void updateRegister(int value) override;
	int getRegisterValue() override;

private:
	typedef RegisterCrystal super;

	cocos2d::Sprite* crystal;
};
