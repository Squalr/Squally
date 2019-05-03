#pragma once

#include "Objects/Isometric/PointerTrace/RegisterCrystals/RegisterCrystal.h"

namespace cocos2d
{
	class Sprite;
}

class EdiCrystal : public RegisterCrystal
{
public:
	static EdiCrystal* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyEdiCrystal;

protected:
	EdiCrystal(cocos2d::ValueMap& initProperties);
	~EdiCrystal();

	void onEnter() override;
	void initializePositions() override;
	void updateRegister(int value) override;

private:
	typedef RegisterCrystal super;

	cocos2d::Sprite* crystal;
};
