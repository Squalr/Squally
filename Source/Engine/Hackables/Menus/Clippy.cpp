#include "Clippy.h"

#include "Engine/Dialogue/SpeechBubble.h"

using namespace cocos2d;

Clippy::Clippy()
{
	this->animationNode = Node::create();
	this->speechBubble = SpeechBubble::create(false);

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

void Clippy::runDialogue(LocalizedString* localizedString, std::string soundResource)
{
	if (this->isEnabled)
	{
		this->speechBubble->runDialogue(localizedString, soundResource, SpeechBubble::InfiniteDuration, nullptr, SpeechBubble::Direction::ExpandLeft);
	}
}

void Clippy::setIsEnabled(bool isEnabled)
{
	this->isEnabled = isEnabled;
}

bool Clippy::getIsEnabled()
{
	return this->isEnabled;
}
