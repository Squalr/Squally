#include "Minotaur.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Minotaur::MapKey = "minotaur";

Minotaur* Minotaur::deserialize(ValueMap& properties)
{
	Minotaur* instance = new Minotaur(properties);

	instance->autorelease();

	return instance;
}

Minotaur::Minotaur(ValueMap& properties) : super(properties,
	Minotaur::MapKey,
	EntityResources::Enemies_UnderflowRuins_Minotaur_Animations,
	EntityResources::Enemies_UnderflowRuins_Minotaur_Emblem,
	Size(278.0f, 288.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Minotaur::~Minotaur()
{
}

Vec2 Minotaur::getDialogueOffset()
{
	return Vec2(-48.0f, -196.0f);
}

LocalizedString* Minotaur::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_Minotaur::create();
}
