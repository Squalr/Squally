#include "KillingMachine6.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string KillingMachine6::MapKey = "killing-machine-6";

KillingMachine6* KillingMachine6::deserialize(ValueMap& properties)
{
	KillingMachine6* instance = new KillingMachine6(properties);

	instance->autorelease();

	return instance;
}

KillingMachine6::KillingMachine6(ValueMap& properties) : super(properties,
	KillingMachine6::MapKey,
	EntityResources::Misc_UnderflowRuins_KillingMachine6_Animations,
	EntityResources::Misc_UnderflowRuins_KillingMachine6_Emblem,
	CSize(2048.0f, 1536.0f),
	0.25f,
	Vec2(0.0f, 0.0f))
{
}

KillingMachine6::~KillingMachine6()
{
}

Vec2 KillingMachine6::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* KillingMachine6::getEntityName()
{
	return Strings::Common_Empty::create();
}
