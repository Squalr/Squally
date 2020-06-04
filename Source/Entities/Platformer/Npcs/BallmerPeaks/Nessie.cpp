#include "Nessie.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Nessie::MapKey = "nessie";

Nessie* Nessie::deserialize(ValueMap& properties)
{
	Nessie* instance = new Nessie(properties);

	instance->autorelease();

	return instance;
}

Nessie::Nessie(ValueMap& properties) : super(properties,
	Nessie::MapKey,
	EntityResources::Npcs_BallmerPeaks_Nessie_Animations,
	EntityResources::Npcs_BallmerPeaks_Nessie_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Nessie::~Nessie()
{
}

Vec2 Nessie::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Nessie::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BallmerPeaks_Nessie::create();
}
