#include "IsometricDecorObject.h"

IsometricDecorObject* IsometricDecorObject::create(ValueMap* initProperties)
{
	IsometricDecorObject* instance = new IsometricDecorObject(initProperties);

	instance->autorelease();

	return instance;
}

IsometricDecorObject::IsometricDecorObject(ValueMap* initProperties) : HackableObject(initProperties)
{
}

IsometricDecorObject::~IsometricDecorObject()
{
}
