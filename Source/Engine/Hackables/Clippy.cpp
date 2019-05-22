#include "Clippy.h"

#include "Engine/Dialogue/SpeechBubble.h"

using namespace cocos2d;

Clippy::Clippy()
{
	this->animationNode = Node::create();
	this->speechBubble = SpeechBubble::create();

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
