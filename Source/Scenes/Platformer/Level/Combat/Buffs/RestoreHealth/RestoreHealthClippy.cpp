#include "RestoreHealthClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Sound/Sound.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Menus/Hacking/ClippyHelp/RestoreHealthInc.h"

using namespace cocos2d;

RestoreHealthClippy* RestoreHealthClippy::create()
{
	RestoreHealthClippy* instance = new RestoreHealthClippy();

	instance->autorelease();

	return instance;
}

RestoreHealthClippy::RestoreHealthClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);
	this->droidChatterSound = Sound::create(SoundResources::Platformer_Entities_Droid_DroidChatter);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
	this->addChild(this->droidChatterSound);
}

RestoreHealthClippy::~RestoreHealthClippy()
{
}

Clippy* RestoreHealthClippy::innerClone()
{
	return RestoreHealthClippy::create();
}

void RestoreHealthClippy::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->speechBubble->runDialogue(Strings::Menus_Hacking_ClippyHelp_RestoreHealthInc::create());
	this->droidChatterSound->play();
}
