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

void PlatformerDecorObject::onHackerModeEnable()
{
	super::onHackerModeEnable();

	this->setVisible(false);
}

void PlatformerDecorObject::onHackerModeDisable()
{
	super::onHackerModeDisable();

	this->setVisible(true);
}
