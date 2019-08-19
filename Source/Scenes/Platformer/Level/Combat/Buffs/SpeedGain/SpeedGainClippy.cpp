#include "SpeedGainClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Sound/Sound.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Hacking/ClippyHelp/SpeedGainMul.h"

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
	this->droidChatterSound = Sound::create(SoundResources::Platformer_Entities_Droid_DroidChatter);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
	this->addChild(this->droidChatterSound);
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

	this->speechBubble->runDialogue(Strings::Hacking_ClippyHelp_SpeedGainMul::create());
	this->droidChatterSound->play();
}
