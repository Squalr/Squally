#include "Xenon.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Xenon::MapKey = "xenon";

Xenon* Xenon::deserialize(ValueMap& properties)
{
	Xenon* instance = new Xenon(properties);

	instance->autorelease();

	return instance;
}

Xenon::Xenon(ValueMap& properties) : super(properties,
	Xenon::MapKey,
	EntityResources::Npcs_VoidStar_Xenon_Animations,
	EntityResources::Npcs_VoidStar_Xenon_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Xenon::~Xenon()
{
}

Vec2 Xenon::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Xenon::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Xenon::create();
}
