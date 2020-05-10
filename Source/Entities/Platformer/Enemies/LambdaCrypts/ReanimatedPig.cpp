#include "ReanimatedPig.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ReanimatedPig::MapKey = "reanimated-pig";

ReanimatedPig* ReanimatedPig::deserialize(ValueMap& properties)
{
	ReanimatedPig* instance = new ReanimatedPig(properties);

	instance->autorelease();

	return instance;
}

ReanimatedPig::ReanimatedPig(ValueMap& properties) : super(properties,
	ReanimatedPig::MapKey,
	EntityResources::Enemies_LambdaCrypts_ReanimatedPig_Animations,
	EntityResources::Enemies_LambdaCrypts_ReanimatedPig_Emblem,
	Size(256.0f, 240.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

ReanimatedPig::~ReanimatedPig()
{
}

Vec2 ReanimatedPig::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* ReanimatedPig::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_ReanimatedPig::create();
}
