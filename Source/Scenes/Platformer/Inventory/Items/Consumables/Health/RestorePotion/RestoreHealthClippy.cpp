#include "RestoreHealthClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

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

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
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

	this->runDialogue(Strings::Menus_Hacking_ClippyHelp_RestoreHealthInc::create(), SoundResources::Platformer_Entities_Droid_DroidChatter);
}
