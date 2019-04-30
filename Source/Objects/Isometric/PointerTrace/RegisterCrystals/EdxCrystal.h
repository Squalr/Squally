#pragma once

#include "Objects/Isometric/PointerTrace/RegisterCrystals/RegisterCrystal.h"

namespace cocos2d
{
	class Sprite;
}

class EdxCrystal : public RegisterCrystal
{
public:
	static EdxCrystal* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyEdxCrystal;

protected:
	EdxCrystal(cocos2d::ValueMap& initProperties);
	~EdxCrystal();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef RegisterCrystal super;

	cocos2d::Sprite* crystal;
};
