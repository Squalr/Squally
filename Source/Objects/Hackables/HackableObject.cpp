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

	this->hackableMenuButton = MenuSprite::create(Resources::Menus_Buttons_SettingsButton, Resources::Menus_Buttons_SettingsButton, Resources::Menus_Buttons_SettingsButton);

	this->addChild(this->hackableMenuButton);
}

HackableObject::~HackableObject()
{
}

void HackableObject::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	this->setPosition(this->parent->getParent()->convertToWorldSpace(this->parent->getPosition()) + this->buttonOffset);

	Node::draw(renderer, transform, flags);
}
