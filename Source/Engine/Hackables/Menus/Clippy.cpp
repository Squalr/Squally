#include "Clippy.h"

#include "Engine/Dialogue/SpeechBubble.h"

using namespace cocos2d;

std::map<std::string, bool> Clippy::UniqueRunMap = std::map<std::string, bool>();

Clippy::Clippy(std::string uniqueRunKey)
{
	this->animationNode = Node::create();
	this->speechBubble = SpeechBubble::create(false);
	this->isEnabled = true;
	this->uniqueRunKey = uniqueRunKey;

	if (!uniqueRunKey.empty() && !Clippy::UniqueRunMap.contains(uniqueRunKey))
	{
		Clippy::UniqueRunMap[uniqueRunKey] = false;
	}

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
		if (this->isFirstUniqueRun())
		{
			this->speechBubble->runDialogue(localizedString, soundResource, SpeechBubble::InfiniteDuration, nullptr, SpeechBubble::Direction::ExpandLeft);
			
			Clippy::UniqueRunMap[this->uniqueRunKey] = true;
		}
		else
		{
			this->speechBubble->runDialogue(localizedString, "", SpeechBubble::InfiniteDuration, nullptr, SpeechBubble::Direction::ExpandLeft, true);
		}
	}
}

bool Clippy::isFirstUniqueRun()
{
	if (this->uniqueRunKey.empty() || !Clippy::UniqueRunMap.contains(this->uniqueRunKey) || !Clippy::UniqueRunMap[this->uniqueRunKey])
	{
		return true;
	}

	return false;
}

void Clippy::setIsEnabled(bool isEnabled)
{
	this->isEnabled = isEnabled;
}

bool Clippy::getIsEnabled()
{
	return this->isEnabled;
}
