#include "PlatformerDecorObject.h"

using namespace cocos2d;

PlatformerDecorObject* PlatformerDecorObject::create(ValueMap& properties)
{
	PlatformerDecorObject* instance = new PlatformerDecorObject(properties);

	instance->autorelease();

	return instance;
}

PlatformerDecorObject::PlatformerDecorObject(ValueMap& properties) : super(properties)
{
}

PlatformerDecorObject::~PlatformerDecorObject()
{
}
