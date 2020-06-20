#include "VampireLord.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VampireLord::MapKey = "vampire-lord";

VampireLord* VampireLord::deserialize(ValueMap& properties)
{
	VampireLord* instance = new VampireLord(properties);

	instance->autorelease();

	return instance;
}

VampireLord::VampireLord(ValueMap& properties) : super(properties,
	VampireLord::MapKey,
	EntityResources::Enemies_CastleValgrind_VampireLord_Animations,
	EntityResources::Enemies_CastleValgrind_VampireLord_Emblem,
	Size(240.0f, 312.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

VampireLord::~VampireLord()
{
}

Vec2 VampireLord::getDialogueOffset()
{
	return Vec2(-32.0f, -160.0f);
}

LocalizedString* VampireLord::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_VampireLord::create();
}
