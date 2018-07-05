#include "PlatformerDecorObject.h"

PlatformerDecorObject* PlatformerDecorObject::create(ValueMap* initProperties)
{
	PlatformerDecorObject* instance = new PlatformerDecorObject(initProperties);

	instance->autorelease();

	return instance;
}

PlatformerDecorObject::PlatformerDecorObject(ValueMap* initProperties) : HackableObject(initProperties)
{
}

PlatformerDecorObject::~PlatformerDecorObject()
{
}
