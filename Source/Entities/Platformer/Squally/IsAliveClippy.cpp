#include "IsAliveClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Sound/WorldSound.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

IsAliveClippy* IsAliveClippy::create()
{
	IsAliveClippy* instance = new IsAliveClippy();

	instance->autorelease();

	return instance;
}

IsAliveClippy::IsAliveClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
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

	this->speechBubble->runDialogue(Strings::Menus_Hacking_ClippyHelp_IsAliveRetVal::create(), SoundResources::Platformer_Entities_Droid_DroidChatter, SpeechBubble::InfiniteDuration);
}
