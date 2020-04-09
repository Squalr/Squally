#pragma once

#include "Objects/Isometric/PointerTrace/RegisterCrystals/RegisterCrystal.h"

namespace cocos2d
{
	class Sprite;
}

class EdiCrystal : public RegisterCrystal
{
public:
	static EdiCrystal* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	EdiCrystal(cocos2d::ValueMap& properties);
	virtual ~EdiCrystal();

	void onEnter() override;
	void initializePositions() override;
	void updateRegister(int value) override;
	int getRegisterValue() override;

private:
	typedef RegisterCrystal super;

	cocos2d::Sprite* crystal;
};
