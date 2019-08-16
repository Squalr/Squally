#pragma once

#include "Objects/Isometric/PointerTrace/RegisterCrystals/RegisterCrystal.h"

namespace cocos2d
{
	class Sprite;
}

class EbxCrystal : public RegisterCrystal
{
public:
	static EbxCrystal* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyEbxCrystal;

protected:
	EbxCrystal(cocos2d::ValueMap& properties);
	~EbxCrystal();

	void onEnter() override;
	void initializePositions() override;
	void updateRegister(int value) override;
	int getRegisterValue() override;

private:
	typedef RegisterCrystal super;

	cocos2d::Sprite* crystal;
};
