#include "HackableAttribute.h"

#include "Engine/Hackables/Clippy.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Localization/LocalizedString.h"

HackableAttribute::HackableAttribute(int requiredEq, float duration, std::string iconResource, LocalizedString* name, HackablePreview* hackablePreview, Clippy* clippy)
{
	this->requiredEq = requiredEq;
	this->duration = duration;
	this->iconResource = iconResource;
	this->name = name;
	this->hackablePreview = hackablePreview;
	this->elapsedDuration = this->duration;
	this->clippy = clippy;

	if (this->hackablePreview != nullptr)
	{
		this->hackablePreview->retain();
	}

	if (this->clippy != nullptr)
	{
		this->clippy->retain();
	}

	if (this->name != nullptr)
	{
		this->addChild(this->name); // Retain with event listening
	}
}

HackableAttribute::~HackableAttribute()
{
	if (this->hackablePreview != nullptr)
	{
		this->hackablePreview->release();
	}

	if (this->clippy != nullptr)
	{
		this->clippy->release();
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

int HackableAttribute::getRequiredEq()
{
	return this->requiredEq;
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

Clippy* HackableAttribute::getClippy()
{
	return this->clippy;
}
