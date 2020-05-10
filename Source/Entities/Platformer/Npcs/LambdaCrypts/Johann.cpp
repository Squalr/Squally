#include "Johann.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Johann::MapKey = "johann";

Johann* Johann::deserialize(ValueMap& properties)
{
	Johann* instance = new Johann(properties);

	instance->autorelease();

	return instance;
}

Johann::Johann(ValueMap& properties) : super(properties,
	Johann::MapKey,
	EntityResources::Npcs_LambdaCrypts_Johann_Animations,
	EntityResources::Npcs_LambdaCrypts_Johann_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Johann::~Johann()
{
}

Vec2 Johann::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Johann::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Johann::create();
}
