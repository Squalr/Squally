#include "IsAliveClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Sound/Sound.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Hacking/ClippyHelp/IsAliveRetVal.h"

using namespace cocos2d;

IsAliveClippy* IsAliveClippy::create()
{
	IsAliveClippy* instance = new IsAliveClippy();

	instance->autorelease();

	return instance;
}

IsAliveClippy::IsAliveClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Misc_DaemonsHallow_FlyBot_Animations);
	this->droidChatterSound = Sound::create(SoundResources::Platformer_Entities_Droid_DroidChatter);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
	this->addChild(this->droidChatterSound);
}

IsAliveClippy::~IsAliveClippy()
{
}

Clippy* IsAliveClippy::innerClone()
{
	return IsAliveClippy::create();
}

void IsAliveClippy::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->speechBubble->runDialogue(Strings::Hacking_ClippyHelp_IsAliveRetVal::create());
	this->droidChatterSound->play();
}
