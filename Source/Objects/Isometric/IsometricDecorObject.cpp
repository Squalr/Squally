#include "IsometricDecorObject.h"

using namespace cocos2d;

IsometricDecorObject* IsometricDecorObject::create(ValueMap& properties)
{
	IsometricDecorObject* instance = new IsometricDecorObject(properties);

	instance->autorelease();

	return instance;
}

IsometricDecorObject::IsometricDecorObject(ValueMap& properties) : super(properties)
{
}

IsometricDecorObject::~IsometricDecorObject()
{
}
