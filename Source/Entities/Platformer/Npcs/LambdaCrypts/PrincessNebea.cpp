#include "PrincessNebea.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PrincessNebea::MapKey = "princess-nebea";

PrincessNebea* PrincessNebea::deserialize(ValueMap& properties)
{
	PrincessNebea* instance = new PrincessNebea(properties);

	instance->autorelease();

	return instance;
}

PrincessNebea::PrincessNebea(ValueMap& properties) : super(properties,
	PrincessNebea::MapKey,
	EntityResources::Npcs_LambdaCrypts_PrincessNebea_Animations,
	EntityResources::Npcs_LambdaCrypts_PrincessNebea_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

PrincessNebea::~PrincessNebea()
{
}

Vec2 PrincessNebea::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* PrincessNebea::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_PrincessNebea::create();
}
