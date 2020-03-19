#pragma once

#include "Objects/Isometric/PointerTrace/RegisterCrystals/RegisterCrystal.h"

namespace cocos2d
{
	class Sprite;
}

class EdxCrystal : public RegisterCrystal
{
public:
	static EdxCrystal* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	EdxCrystal(cocos2d::ValueMap& properties);
	virtual ~EdxCrystal();

	void onEnter() override;
	void initializePositions() override;
	void updateRegister(int value) override;
	int getRegisterValue() override;

private:
	typedef RegisterCrystal super;

	cocos2d::Sprite* crystal;
};
