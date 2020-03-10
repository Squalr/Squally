#include "SpeedGainClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

SpeedGainClippy* SpeedGainClippy::create()
{
	SpeedGainClippy* instance = new SpeedGainClippy();

	instance->autorelease();

	return instance;
}

SpeedGainClippy::SpeedGainClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

SpeedGainClippy::~SpeedGainClippy()
{
}

Clippy* SpeedGainClippy::innerClone()
{
	return SpeedGainClippy::create();
}

void SpeedGainClippy::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->runDialogue(Strings::Menus_Hacking_ClippyHelp_Items_SpeedRune_SpeedGainMul::create(), SoundResources::Platformer_Entities_Droid_DroidChatter);
}
