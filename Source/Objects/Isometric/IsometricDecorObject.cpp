#include "IsometricDecorObject.h"

using namespace cocos2d;

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
