#include "DartNopClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

DartNopClippy* DartNopClippy::create()
{
	DartNopClippy* instance = new DartNopClippy();

	instance->autorelease();

	return instance;
}

DartNopClippy::DartNopClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

DartNopClippy::~DartNopClippy()
{
}

Clippy* DartNopClippy::innerClone()
{
	return DartNopClippy::create();
}

void DartNopClippy::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->speechBubble->runDialogue(Strings::Menus_Hacking_ClippyHelp_DartNop::create(), SoundResources::Platformer_Entities_Droid_DroidChatter, SpeechBubble::InfiniteDuration);
}
