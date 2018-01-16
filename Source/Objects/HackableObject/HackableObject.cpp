#include "HackableObject.h"

HackableObject* HackableObject::create(Node* parentNode, Vec2 offset)
{
	HackableObject* hackableObject = new HackableObject(parentNode, offset);

	hackableObject->autorelease();

	return hackableObject;
}

HackableObject::HackableObject(Node* parentNode, Vec2 offset)
{
	this->parent = parentNode;
	this->buttonOffset = offset;
}

HackableObject::~HackableObject()
{
}

void HackableObject::update(float dt)
{
	this->setPosition(this->parent->getPosition() + this->buttonOffset);
}
