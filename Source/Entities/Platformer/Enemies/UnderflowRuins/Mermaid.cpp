#include "Mermaid.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Mermaid::MapKey = "mermaid";

Mermaid* Mermaid::deserialize(ValueMap& properties)
{
	Mermaid* instance = new Mermaid(properties);

	instance->autorelease();

	return instance;
}

Mermaid::Mermaid(ValueMap& properties) : super(properties,
	Mermaid::MapKey,
	EntityResources::Enemies_UnderflowRuins_Mermaid_Animations,
	EntityResources::Enemies_UnderflowRuins_Mermaid_Emblem,
	Size(172.0f, 296.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Mermaid::~Mermaid()
{
}

Vec2 Mermaid::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Mermaid::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_Mermaid::create();
}
