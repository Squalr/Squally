#include "IncrementHealthClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

IncrementHealthClippy* IncrementHealthClippy::create()
{
	IncrementHealthClippy* instance = new IncrementHealthClippy();

	instance->autorelease();

	return instance;
}

IncrementHealthClippy::IncrementHealthClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

IncrementHealthClippy::~IncrementHealthClippy()
{
}

Clippy* IncrementHealthClippy::innerClone()
{
	return IncrementHealthClippy::create();
}

void IncrementHealthClippy::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->runDialogue(Strings::Menus_Hacking_ClippyHelp_Items_IncrementHealthFlask_IncrementHealthInc::create(), SoundResources::Platformer_Entities_Droid_DroidChatter);
}
