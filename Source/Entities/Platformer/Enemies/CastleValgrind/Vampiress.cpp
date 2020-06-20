#include "Vampiress.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Vampiress::MapKey = "vampiress";

Vampiress* Vampiress::deserialize(ValueMap& properties)
{
	Vampiress* instance = new Vampiress(properties);

	instance->autorelease();

	return instance;
}

Vampiress::Vampiress(ValueMap& properties) : super(properties,
	Vampiress::MapKey,
	EntityResources::Enemies_CastleValgrind_Vampiress_Animations,
	EntityResources::Enemies_CastleValgrind_Vampiress_Emblem,
	Size(96.0f, 236.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Vampiress::~Vampiress()
{
}

Vec2 Vampiress::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Vampiress::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_Vampiress::create();
}
