#include "Perceptron.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Perceptron::MapKey = "perceptron";

Perceptron* Perceptron::deserialize(ValueMap& properties)
{
	Perceptron* instance = new Perceptron(properties);

	instance->autorelease();

	return instance;
}

Perceptron::Perceptron(ValueMap& properties) : super(properties,
	Perceptron::MapKey,
	EntityResources::Enemies_VoidStar_Perceptron_Animations,
	EntityResources::Enemies_VoidStar_Perceptron_Emblem,
	CSize(720.0f, 840.0f),
	0.6f)
{
}

Perceptron::~Perceptron()
{
}

Vec2 Perceptron::getDialogueOffset()
{
	return Vec2(0.0f, -172.0f);
}

LocalizedString* Perceptron::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_Perceptron::create();
}
