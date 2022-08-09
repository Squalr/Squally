#include "KillingMachine5.h"

#include "cocos/math/CCGeometry.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string KillingMachine5::MapKey = "killing-machine-5";

KillingMachine5* KillingMachine5::deserialize(ValueMap& properties)
{
	KillingMachine5* instance = new KillingMachine5(properties);

	instance->autorelease();

	return instance;
}

KillingMachine5::KillingMachine5(ValueMap& properties) : super(properties,
	KillingMachine5::MapKey,
	EntityResources::Misc_UnderflowRuins_KillingMachine5_Animations,
	EntityResources::Misc_UnderflowRuins_KillingMachine5_Emblem,
	CSize(2048.0f, 1536.0f),
	0.25f,
	Vec2(0.0f, 0.0f))
{
	this->animationNode->setScaleX(-this->animationNode->getScaleX());
}

KillingMachine5::~KillingMachine5()
{
}

Vec2 KillingMachine5::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* KillingMachine5::getEntityName()
{
	return Strings::Common_Empty::create();
}
