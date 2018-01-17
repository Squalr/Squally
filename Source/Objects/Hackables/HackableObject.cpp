#include "HackableObject.h"

const std::string HackableObject::HackableObjectEditEvent = "hackable_object_edit_event";

HackableObject* HackableObject::create(Node* parentNode, std::string previewResource, Vec2 offset)
{
	HackableObject* hackableObject = new HackableObject(parentNode, previewResource, offset);

	hackableObject->autorelease();

	return hackableObject;
}

HackableObject::HackableObject(Node* parentNode, std::string previewResource, Vec2 offset)
{
	this->parent = parentNode;
	this->previewSpriteResource = previewResource;
	this->buttonOffset = offset;

	this->hackableMenuButton = MenuSprite::create(Resources::Menus_Buttons_HackButton, Resources::Menus_Buttons_HackButtonHover, Resources::Menus_Buttons_HackButtonClick);
	this->hackableMenuButton->setClickCallback(CC_CALLBACK_1(HackableObject::onObjectClick, this));

	this->addChild(this->hackableMenuButton);
}

HackableObject::~HackableObject()
{
}

void HackableObject::onObjectClick(MenuSprite* menuSprite)
{
	this->getEventDispatcher()->dispatchCustomEvent(
		HackableObject::HackableObjectEditEvent,
		&HackableObject::HackableObjectEditArgs(this, this->previewSpriteResource)
	);
}

void HackableObject::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	this->setPosition(this->parent->getParent()->convertToWorldSpace(this->parent->getPosition()) + this->buttonOffset);

	Node::draw(renderer, transform, flags);
}
