#include "HasteClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

HasteClippy* HasteClippy::create()
{
	HasteClippy* instance = new HasteClippy();

	instance->autorelease();

	return instance;
}

HasteClippy::HasteClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

HasteClippy::~HasteClippy()
{
}

Clippy* HasteClippy::innerClone()
{
	return HasteClippy::create();
}

void HasteClippy::startDialogue()
{
	this->runDialogue(
		Strings::Menus_Hacking_Abilities_Haste_HasteClippy::create()
			->setStringReplacementVariables(Strings::Menus_Hacking_Abilities_Haste_ReduceHaste::create()),
		SoundResources::Platformer_Entities_Droid_DroidChatter
	);
}
