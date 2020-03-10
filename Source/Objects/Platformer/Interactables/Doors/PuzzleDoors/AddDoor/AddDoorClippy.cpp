#include "AddDoorClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

AddDoorClippy* AddDoorClippy::create()
{
	AddDoorClippy* instance = new AddDoorClippy();

	instance->autorelease();

	return instance;
}

AddDoorClippy::AddDoorClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

AddDoorClippy::~AddDoorClippy()
{
}

Clippy* AddDoorClippy::innerClone()
{
	return AddDoorClippy::create();
}

void AddDoorClippy::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->runDialogue(Strings::Menus_Hacking_ClippyHelp_Objects_PuzzleDoors_AddDoor_Add::create(), SoundResources::Platformer_Entities_Droid_DroidChatter);
}
