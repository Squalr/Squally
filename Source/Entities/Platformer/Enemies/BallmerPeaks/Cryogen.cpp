#include "Cryogen.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Cryogen::MapKey = "cryogen";

Cryogen* Cryogen::deserialize(ValueMap& properties)
{
	Cryogen* instance = new Cryogen(properties);

	instance->autorelease();

	return instance;
}

Cryogen::Cryogen(ValueMap& properties) : super(properties,
	Cryogen::MapKey,
	EntityResources::Enemies_BallmerPeaks_Cryogen_Animations,
	EntityResources::Enemies_BallmerPeaks_Cryogen_Emblem,
	Size(420.0f, 420.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

Cryogen::~Cryogen()
{
}

Vec2 Cryogen::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Cryogen::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_BallmerPeaks_Cryogen::create();
}
