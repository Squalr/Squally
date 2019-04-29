#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class EaxCrystal : public HackableObject
{
public:
	static EaxCrystal* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyEaxCrystal;

protected:
	EaxCrystal(cocos2d::ValueMap& initProperties);
	~EaxCrystal();

private:
	typedef HackableObject super;

	cocos2d::Sprite* crystal;
};
