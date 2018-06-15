#include "DecorObject.h"

DecorObject* DecorObject::create()
{
	DecorObject* instance = new DecorObject();

	instance->autorelease();

	return instance;
}

DecorObject::DecorObject()
{
}

DecorObject::~DecorObject()
{
}
