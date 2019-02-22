#include "Equipable.h"

using namespace cocos2d;

Equipable::Equipable(LocalizedString* name, std::string iconResource) : super(name, iconResource)
{
}

Equipable::~Equipable()
{
}

Vec2 Equipable::getDisplayOffset()
{
	return Vec2::ZERO;
}
