#include "KillingMachine2.h"

#include "cocos/math/CCGeometry.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string KillingMachine2::MapKey = "killing-machine-2";

KillingMachine2* KillingMachine2::deserialize(ValueMap& properties)
{
	KillingMachine2* instance = new KillingMachine2(properties);

	instance->autorelease();

	return instance;
}

KillingMachine2::KillingMachine2(ValueMap& properties) : super(properties,
	KillingMachine2::MapKey,
	EntityResources::Misc_UnderflowRuins_KillingMachine2_Animations,
	EntityResources::Misc_UnderflowRuins_KillingMachine2_Emblem,
	CSize(2048.0f, 1536.0f),
	0.25f,
	Vec2(0.0f, 0.0f))
{
	this->animationNode->setScaleX(-this->animationNode->getScaleX());
}

KillingMachine2::~KillingMachine2()
{
}

Vec2 KillingMachine2::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* KillingMachine2::getEntityName()
{
	return Strings::Common_Empty::create();
}
