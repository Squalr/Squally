#include "MulDoorClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

MulDoorClippy* MulDoorClippy::create()
{
	MulDoorClippy* instance = new MulDoorClippy();

	instance->autorelease();

	return instance;
}

MulDoorClippy::MulDoorClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

MulDoorClippy::~MulDoorClippy()
{
}

Clippy* MulDoorClippy::innerClone()
{
	return MulDoorClippy::create();
}

void MulDoorClippy::startDialogue()
{
	this->runDialogue(Strings::Menus_Hacking_ClippyHelp_Objects_PuzzleDoors_MulDoor_IMul::create(), SoundResources::Platformer_Entities_Droid_DroidChatter);
}
