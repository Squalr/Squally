#include "Gear.h"

using namespace cocos2d;

Gear::Gear(LocalizedString* name, std::string iconResource, int defense) : super(name, iconResource)
{
	this->defense = defense;
}

Gear::~Gear()
{
}

int Gear::getDefense()
{
	return this->defense;
}
