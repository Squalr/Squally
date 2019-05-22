#include "WindClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"

#include "Strings/Hacking/ClippyHelp/WindNop.h"

using namespace cocos2d;

WindClippy* WindClippy::create()
{
	WindClippy* instance = new WindClippy();

	instance->autorelease();

	return instance;
}

WindClippy::WindClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Misc_DaemonsHallow_FlyBot_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

WindClippy::~WindClippy()
{
}

Clippy* WindClippy::clone()
{
	return WindClippy::create();
}

void WindClippy::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->speechBubble->runDialogue(Strings::Hacking_ClippyHelp_WindNop::create());
}
