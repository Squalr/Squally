#include "HackableObject.h"

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

void HackableObject::onEnterTransitionDidFinish()
{
	Node::onEnterTransitionDidFinish();

	HackableEvents::registerHackable(HackableEvents::HackableObjectRegisterArgs(this));
}

void HackableObject::bindHackableButton(MenuSprite* hackableButton)
{
	this->boundHackableButton = hackableButton;

	if (this->codeList->size() <= 0 && this->dataList->size() <= 0)
	{
		this->boundHackableButton->setVisible(false);
	}
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
	HackableEvents::editHackable(HackableEvents::HackableObjectEditArgs(this, this->getParent()->convertToWorldSpace(this->getPosition())));
}

void HackableObject::registerData(HackableData* hackableData)
{
	hackableData->retain();
	this->dataList->push_back(hackableData);

	if (this->boundHackableButton != nullptr)
	{
		this->boundHackableButton->setVisible(true);
	}
}

void HackableObject::registerCode(HackableCode* hackableCode)
{
	hackableCode->retain();
	this->codeList->push_back(hackableCode);

	if (this->boundHackableButton != nullptr)
	{
		this->boundHackableButton->setVisible(true);
	}
}

void HackableObject::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	if (this->boundHackableButton != nullptr)
	{
		this->boundHackableButton->setPosition(this->getParent()->convertToWorldSpace(this->getPosition()) + this->buttonOffset);
	}

	Node::draw(renderer, transform, flags);
}
