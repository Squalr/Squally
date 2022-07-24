#include "KillingMachine1.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string KillingMachine1::MapKey = "killing-machine-1";

KillingMachine1* KillingMachine1::deserialize(ValueMap& properties)
{
	KillingMachine1* instance = new KillingMachine1(properties);

	instance->autorelease();

	return instance;
}

KillingMachine1::KillingMachine1(ValueMap& properties) : super(properties,
	KillingMachine1::MapKey,
	EntityResources::Misc_UnderflowRuins_KillingMachine1_Animations,
	EntityResources::Misc_UnderflowRuins_KillingMachine1_Emblem,
	CSize(2048.0f, 1536.0f),
	0.25f,
	Vec2(0.0f, 0.0f))
{
}

KillingMachine1::~KillingMachine1()
{
}

Vec2 KillingMachine1::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* KillingMachine1::getEntityName()
{
	return Strings::Common_Empty::create();
}
