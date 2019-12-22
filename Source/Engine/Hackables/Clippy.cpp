#include "Clippy.h"

#include "Engine/Dialogue/SpeechBubble.h"

using namespace cocos2d;

Clippy::Clippy()
{
	this->animationNode = Node::create();
	this->speechBubble = SpeechBubble::create(false);
	this->cloneRef = nullptr;

	this->isEnabled = false;
	this->setVisible(false);

	this->addChild(this->animationNode);
	this->addChild(this->speechBubble);
}

Clippy::~Clippy()
{
}

void Clippy::initializePositions()
{
	super::initializePositions();

	this->speechBubble->setPosition(Vec2(0.0f, 112.0f));
}

Clippy* Clippy::clone()
{
	Clippy* clippy = this->innerClone();

	clippy->setIsEnabled(this->getIsEnabled());
	clippy->cloneRef = this;

	return clippy;
}

Clippy* Clippy::refClone()
{
	Clippy* clippy = this->clone();
	
	clippy->cloneRef = this;

	return clippy;
}

void Clippy::runDialogue(LocalizedString* localizedString, std::string soundResource)
{
	if (this->isEnabled)
	{
		this->speechBubble->runDialogue(localizedString, soundResource, SpeechBubble::InfiniteDuration);
	}
}

void Clippy::setIsEnabled(bool isEnabled)
{
	this->isEnabled = isEnabled;
}

bool Clippy::getIsEnabled()
{
	if (this->cloneRef != nullptr)
	{
		return this->cloneRef->getIsEnabled();
	}

	return this->isEnabled;
}
