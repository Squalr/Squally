#include "HackableObject.h"

#include "Events/HackableEvents.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/UI/Controls/MenuSprite.h"

using namespace cocos2d;

HackableObject::HackableObject(ValueMap* initProperties) : SerializableObject(initProperties)
{
	this->dataList = std::vector<HackableData*>();
	//this->hackButton = MenuSprite::create(UIResources::Menus_Buttons_CogV2Button, UIResources::Menus_Buttons_CogV2ButtonHover);
	
	//this->hackButton->setVisible(false);

	//this->addChild(this->hackButton);
}

HackableObject::~HackableObject()
{
}

void HackableObject::onEnterTransitionDidFinish()
{
	Node::onEnterTransitionDidFinish();

	//this->hackButton->setClickCallback(CC_CALLBACK_1(HackableObject::onHackableClick, this));

	HackableEvents::registerHackable(HackableEvents::HackableObjectRegisterArgs(this));
}

void HackableObject::pause()
{
	SerializableObject::pause();

	// this->hackButton->resume();
}

Vec2 HackableObject::getButtonOffset()
{
	return Vec2::ZERO;
}

void HackableObject::onHackableClick(MenuSprite* menuSprite)
{
	//Vec2 screenPosition = this->getParent()->convertToWorldSpace(this->getPosition()) + this->getButtonOffset();
	//Vec2 newPosition = this->hackButton->getParent()->convertToNodeSpace(screenPosition);

	//HackableEvents::editHackable(HackableEvents::HackableObjectEditArgs(this, newPosition));
}

void HackableObject::registerData(HackableData* hackableData)
{
	hackableData->retain();
	this->dataList.push_back(hackableData);

	//this->hackButton->setVisible(true);
}

void HackableObject::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
	// A little bit of magic to set the hackable button position
	//Vec2 screenPosition = this->getParent()->convertToWorldSpace(this->getPosition()) + this->getButtonOffset();
	//Vec2 newPosition = this->hackButton->getParent()->convertToNodeSpace(screenPosition);
	//this->hackButton->setPosition(newPosition);

	SerializableObject::visit(renderer, parentTransform, parentFlags);
}
