#include "HackableAttribute.h"

#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Localization/LocalizedString.h"

HackableAttribute::HackableAttribute(float duration, std::string iconResource, LocalizedString* name, HackablePreview* hackablePreview)
{
	this->duration = duration;
	this->iconResource = iconResource;
	this->name = name;
	this->hackablePreview = hackablePreview;
	this->elapsedDuration = this->duration;

	if (this->hackablePreview != nullptr)
	{
		this->hackablePreview->retain();
	}

	this->addChild(name); // Retain with event listening
}

HackableAttribute::~HackableAttribute()
{
	if (this->hackablePreview != nullptr)
	{
		this->hackablePreview->release();
	}
}

void HackableAttribute::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void HackableAttribute::update(float dt)
{
	super::update(dt);

	if (this->elapsedDuration < this->duration)
	{
		this->elapsedDuration += dt;

		if (this->elapsedDuration >= this->duration)
		{
			this->restoreState();
		}
	}
}

void HackableAttribute::resetTimer()
{
	this->elapsedDuration = 0.0f;
}

void HackableAttribute::restoreState()
{
}

void* HackableAttribute::getPointer()
{
	return nullptr;
}

float HackableAttribute::getElapsedDuration()
{
	return this->elapsedDuration;
}

float HackableAttribute::getDuration()
{
	return this->duration;
}

std::string HackableAttribute::getIconResource()
{
	return this->iconResource;
}

LocalizedString* HackableAttribute::getName()
{
	return this->name;
}

HackablePreview* HackableAttribute::getHackablePreview()
{
	return this->hackablePreview;
}
