#include "PlatformerDecorObject.h"

using namespace cocos2d;

PlatformerDecorObject* PlatformerDecorObject::create(ValueMap& initProperties)
{
	PlatformerDecorObject* instance = new PlatformerDecorObject(initProperties);

	instance->autorelease();

	return instance;
}

PlatformerDecorObject::PlatformerDecorObject(ValueMap& initProperties) : super(initProperties)
{
}

PlatformerDecorObject::~PlatformerDecorObject()
{
}
