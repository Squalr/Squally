#include "KillingMachine3.h"

#include "cocos/math/CCGeometry.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string KillingMachine3::MapKey = "killing-machine-3";

KillingMachine3* KillingMachine3::deserialize(ValueMap& properties)
{
	KillingMachine3* instance = new KillingMachine3(properties);

	instance->autorelease();

	return instance;
}

KillingMachine3::KillingMachine3(ValueMap& properties) : super(properties,
	KillingMachine3::MapKey,
	EntityResources::Misc_UnderflowRuins_KillingMachine3_Animations,
	EntityResources::Misc_UnderflowRuins_KillingMachine3_Emblem,
	CSize(2048.0f, 1536.0f),
	0.25f,
	Vec2(0.0f, 0.0f))
{
	// Hack until animation is fixed
	this->animationNode->setScaleX(-this->animationNode->getScaleX());
	this->animationNode->setPosition(Vec2(0.0f, 212.0f));
}

KillingMachine3::~KillingMachine3()
{
}

Vec2 KillingMachine3::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* KillingMachine3::getEntityName()
{
	return Strings::Common_Empty::create();
}
