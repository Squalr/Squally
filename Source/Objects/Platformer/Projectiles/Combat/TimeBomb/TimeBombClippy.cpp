#include "TimeBombClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

TimeBombClippy* TimeBombClippy::create()
{
	TimeBombClippy* instance = new TimeBombClippy();

	instance->autorelease();

	return instance;
}

TimeBombClippy::TimeBombClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

TimeBombClippy::~TimeBombClippy()
{
}

Clippy* TimeBombClippy::innerClone()
{
	return TimeBombClippy::create();
}

void TimeBombClippy::startDialogue()
{
	this->runDialogue(Strings::Common_Squally::create(),
		SoundResources::Platformer_Entities_Droid_DroidChatter
	);
}
