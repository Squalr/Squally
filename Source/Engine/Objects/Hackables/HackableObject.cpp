#include "HackableObject.h"

HackableObject::HackableObject(ValueMap* initProperties) : SerializableObject(initProperties)
{
	this->dataList = new std::vector<HackableData*>();
	this->hackButton = MenuSprite::create(Resources::Menus_Buttons_CogV2Button, Resources::Menus_Buttons_CogV2ButtonHover, Resources::Menus_Buttons_CogV2ButtonClick);
	
	//this->hackButton->setVisible(false);

	this->addChild(this->hackButton);
}

HackableObject::~HackableObject()
{
	delete(this->dataList);
}

void HackableObject::onEnterTransitionDidFinish()
{
	Node::onEnter();

	this->hackButton->setClickCallback(CC_CALLBACK_1(HackableObject::onHackableClick, this));

	HackableEvents::registerHackable(HackableEvents::HackableObjectRegisterArgs(this));
}

void HackableObject::pause()
{
	SerializableObject::pause();

	this->hackButton->resume();
}

Vec2 HackableObject::getButtonOffset()
{
	return Vec2::ZERO;
}

void HackableObject::onHackableClick(MenuSprite* menuSprite)
{
	HackableEvents::editHackable(HackableEvents::HackableObjectEditArgs(this, this->getParent()->convertToWorldSpace(this->getPosition())));
}

void HackableObject::registerData(HackableData* hackableData)
{
	hackableData->retain();
	this->dataList->push_back(hackableData);
}

void HackableObject::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
	// A little bit of magic to set the hackable button position
	Vec2 screenPosition = this->getParent()->convertToWorldSpace(this->getPosition()) + this->getButtonOffset();
	Vec2 newPosition = this->hackButton->getParent()->convertToNodeSpace(screenPosition);
	this->hackButton->setPosition(newPosition);

	SerializableObject::visit(renderer, parentTransform, parentFlags);
}
