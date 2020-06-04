#include "IceGolem.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IceGolem::MapKey = "ice-golem";

IceGolem* IceGolem::deserialize(ValueMap& properties)
{
	IceGolem* instance = new IceGolem(properties);

	instance->autorelease();

	return instance;
}

IceGolem::IceGolem(ValueMap& properties) : super(properties,
	IceGolem::MapKey,
	EntityResources::Enemies_BallmerPeaks_IceGolem_Animations,
	EntityResources::Enemies_BallmerPeaks_IceGolem_Emblem,
	Size(256.0f, 224.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

IceGolem::~IceGolem()
{
}

Vec2 IceGolem::getDialogueOffset()
{
	return Vec2(-32.0f, -160.0f);
}

LocalizedString* IceGolem::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_BallmerPeaks_IceGolem::create();
}
