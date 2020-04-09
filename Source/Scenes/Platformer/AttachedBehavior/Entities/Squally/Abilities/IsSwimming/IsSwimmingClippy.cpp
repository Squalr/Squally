#include "IsSwimmingClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Sound/WorldSound.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

IsSwimmingClippy* IsSwimmingClippy::create()
{
	IsSwimmingClippy* instance = new IsSwimmingClippy();

	instance->autorelease();

	return instance;
}

IsSwimmingClippy::IsSwimmingClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

IsSwimmingClippy::~IsSwimmingClippy()
{
}

Clippy* IsSwimmingClippy::innerClone()
{
	return IsSwimmingClippy::create();
}

void IsSwimmingClippy::startDialogue()
{
	this->runDialogue(Strings::Menus_Hacking_ClippyHelp_Abilities_IsSwimming_IsSwimmingRetVal::create(), SoundResources::Platformer_Entities_Droid_DroidChatter);
}
