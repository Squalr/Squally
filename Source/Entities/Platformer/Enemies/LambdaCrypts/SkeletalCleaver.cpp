#include "SkeletalCleaver.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SkeletalCleaver::MapKey = "skeletal-cleaver";

SkeletalCleaver* SkeletalCleaver::deserialize(ValueMap& properties)
{
	SkeletalCleaver* instance = new SkeletalCleaver(properties);

	instance->autorelease();

	return instance;
}

SkeletalCleaver::SkeletalCleaver(ValueMap& properties) : super(properties,
	SkeletalCleaver::MapKey,
	EntityResources::Enemies_LambdaCrypts_SkeletalCleaver_Animations,
	EntityResources::Enemies_LambdaCrypts_SkeletalCleaver_Emblem,
	Size(128.0f, 312.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletalCleaver::~SkeletalCleaver()
{
}

Vec2 SkeletalCleaver::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* SkeletalCleaver::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_SkeletalCleaver::create();
}
