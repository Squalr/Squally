#include "KillingMachine4.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string KillingMachine4::MapKey = "killing-machine-4";

KillingMachine4* KillingMachine4::deserialize(ValueMap& properties)
{
	KillingMachine4* instance = new KillingMachine4(properties);

	instance->autorelease();

	return instance;
}

KillingMachine4::KillingMachine4(ValueMap& properties) : super(properties,
	KillingMachine4::MapKey,
	EntityResources::Misc_UnderflowRuins_KillingMachine4_Animations,
	EntityResources::Misc_UnderflowRuins_KillingMachine4_Emblem,
	CSize(2048.0f, 1536.0f),
	0.25f,
	Vec2(0.0f, 0.0f))
{
}

KillingMachine4::~KillingMachine4()
{
}

Vec2 KillingMachine4::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* KillingMachine4::getEntityName()
{
	return Strings::Common_Empty::create();
}
