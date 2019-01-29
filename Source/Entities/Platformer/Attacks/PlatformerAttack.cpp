#include "PlatformerAttack.h"

using namespace cocos2d;

PlatformerAttack::PlatformerAttack(std::string iconResource)
{
	this->iconResource = iconResource;
}

std::string PlatformerAttack::getIconResource()
{
	return this->iconResource;
}
