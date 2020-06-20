#include "BoneFiend.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BoneFiend::MapKey = "bone-fiend";

BoneFiend* BoneFiend::deserialize(ValueMap& properties)
{
	BoneFiend* instance = new BoneFiend(properties);

	instance->autorelease();

	return instance;
}

BoneFiend::BoneFiend(ValueMap& properties) : super(properties,
	BoneFiend::MapKey,
	EntityResources::Enemies_LambdaCrypts_BoneFiend_Animations,
	EntityResources::Enemies_LambdaCrypts_BoneFiend_Emblem,
	Size(224.0f, 278.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

BoneFiend::~BoneFiend()
{
}

Vec2 BoneFiend::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* BoneFiend::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_BoneFiend::create();
}
