#include "HackableObject.h"

const std::string HackableObject::HackableObjectEditEvent = "hackable_object_edit_event";

HackableObject::HackableObject()
{
	this->previewSprite = nullptr;
	this->boundHackableButton = nullptr;

	this->dataList = new std::vector<HackableData*>();
	this->codeList = new std::vector<HackableCode*>();
}

HackableObject::~HackableObject()
{
	delete(this->dataList);
	delete(this->codeList);

	if (this->previewSprite != nullptr)
	{
		this->previewSprite->release();
	}
}

void HackableObject::bindHackableButton(MenuSprite* hackableButton)
{
	this->boundHackableButton = hackableButton;
}

void HackableObject::setPreviewImage(std::string previewResource)
{
	this->previewSprite = Sprite::create(previewResource);

	this->previewSprite->retain();
}

void HackableObject::setButtonOffset(Vec2 offset)
{
	this->buttonOffset = offset;
}

void HackableObject::onHackableClick(MenuSprite* menuSprite)
{
	this->getEventDispatcher()->dispatchCustomEvent(
		HackableObject::HackableObjectEditEvent,
		&HackableObject::HackableObjectEditArgs(this, this->previewSprite)
	);
}

void HackableObject::registerData(HackableData* hackableData)
{
	hackableData->retain();
	this->dataList->push_back(hackableData);
}

void HackableObject::registerCode(HackableCode* hackableCode)
{
	hackableCode->retain();
	this->codeList->push_back(hackableCode);
}

void HackableObject::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	if (this->boundHackableButton != nullptr)
	{
		this->boundHackableButton->setPosition(this->getParent()->convertToWorldSpace(this->getPosition()) + this->buttonOffset);
	}
	Node::draw(renderer, transform, flags);
}
