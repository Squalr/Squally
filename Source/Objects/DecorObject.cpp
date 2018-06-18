#include "DecorObject.h"

DecorObject* DecorObject::create(ValueMap* initProperties)
{
	DecorObject* instance = new DecorObject(initProperties);

	instance->autorelease();

	return instance;
}

DecorObject::DecorObject(ValueMap* initProperties) : HackableObject(initProperties)
{
}

DecorObject::~DecorObject()
{
}
