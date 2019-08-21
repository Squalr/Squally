#include "WindClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Sound/Sound.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Menus/Hacking/ClippyHelp/WindNop.h"

using namespace cocos2d;

WindClippy* WindClippy::create()
{
	WindClippy* instance = new WindClippy();

	instance->autorelease();

	return instance;
}

WindClippy::WindClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);
	this->droidChatterSound = Sound::create(SoundResources::Platformer_Entities_Droid_DroidChatter);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
	this->addChild(this->droidChatterSound);
}

WindClippy::~WindClippy()
{
}

Clippy* WindClippy::innerClone()
{
	return WindClippy::create();
}

void WindClippy::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->speechBubble->runDialogue(Strings::Menus_Hacking_ClippyHelp_WindNop::create());
	this->droidChatterSound->play();
}
