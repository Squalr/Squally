#include "OutputBolt.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

OutputBolt* OutputBolt::create()
{
	OutputBolt* instance = new OutputBolt();

	instance->autorelease();

	return instance;
}

OutputBolt::OutputBolt()
{
	this->bolt = Sprite::create(CipherResources::Connections_ConnectionPlug);
	this->helperArrow = Sprite::create(CipherResources::Connections_HelperArrowOutput);

	this->addChild(this->bolt);
	this->addChild(this->helperArrow);
}

OutputBolt::~OutputBolt()
{
}

void OutputBolt::onEnter()
{
	super::onEnter();
}

void OutputBolt::initializePositions()
{
	super::initializePositions();

	const float offsetInit = -20.0f;
	const float offsetEnd = -26.0f;

	this->helperArrow->setPositionY(offsetInit);
	
	this->helperArrow->runAction(
		RepeatForever::create(
			Sequence::create(
				MoveTo::create(1.25f, Vec2(0.0f, offsetInit)),
				MoveTo::create(1.25f, Vec2(0.0f, offsetEnd)),
				nullptr
			)
		)
	);
}

void OutputBolt::initializeListeners()
{
	super::initializeListeners();
}
