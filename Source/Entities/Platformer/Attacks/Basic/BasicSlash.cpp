#include "BasicSlash.h"

#include "Resources/UIResources.h"

#include "Strings/Combat/Attacks/Basic/BasicSlash.h"

using namespace cocos2d;

BasicSlash* BasicSlash::create()
{
	BasicSlash* instance = new BasicSlash();

	instance->autorelease();

	return instance;
}

BasicSlash::BasicSlash() : super(UIResources::Menus_Icons_SwordSlash, 3, 5, 0, 1.5f, 0.15f)
{
}

PlatformerAttack* BasicSlash::clone()
{
	return BasicSlash::create();
}

LocalizedString* BasicSlash::getString()
{
	return Strings::Combat_Attacks_Basic_BasicSlash::create();
}
