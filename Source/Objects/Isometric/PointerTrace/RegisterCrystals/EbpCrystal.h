#pragma once

#include "Objects/Isometric/PointerTrace/RegisterCrystals/RegisterCrystal.h"

namespace cocos2d
{
	class Sprite;
}

class EbpCrystal : public RegisterCrystal
{
public:
	static EbpCrystal* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyEbpCrystal;

protected:
	EbpCrystal(cocos2d::ValueMap& initProperties);
	~EbpCrystal();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef RegisterCrystal super;

	cocos2d::Sprite* crystal;
};
