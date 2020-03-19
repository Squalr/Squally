#pragma once

#include "Objects/Isometric/PointerTrace/RegisterCrystals/RegisterCrystal.h"

namespace cocos2d
{
	class Sprite;
}

class EbpCrystal : public RegisterCrystal
{
public:
	static EbpCrystal* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	EbpCrystal(cocos2d::ValueMap& properties);
	virtual ~EbpCrystal();

	void onEnter() override;
	void initializePositions() override;
	void updateRegister(int value) override;
	int getRegisterValue() override;

private:
	typedef RegisterCrystal super;

	cocos2d::Sprite* crystal;
};
