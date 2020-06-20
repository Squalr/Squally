#include "PenguinGrunt.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PenguinGrunt::MapKey = "penguin-grunt";

PenguinGrunt* PenguinGrunt::deserialize(ValueMap& properties)
{
	PenguinGrunt* instance = new PenguinGrunt(properties);

	instance->autorelease();

	return instance;
}

PenguinGrunt::PenguinGrunt(ValueMap& properties) : super(properties,
	PenguinGrunt::MapKey,
	EntityResources::Enemies_BallmerPeaks_PenguinGrunt_Animations,
	EntityResources::Enemies_BallmerPeaks_PenguinGrunt_Emblem,
	Size(212.0f, 296.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

PenguinGrunt::~PenguinGrunt()
{
}

Vec2 PenguinGrunt::getDialogueOffset()
{
	return Vec2(-32.0f, -128.0f);
}

LocalizedString* PenguinGrunt::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_BallmerPeaks_PenguinGrunt::create();
}
