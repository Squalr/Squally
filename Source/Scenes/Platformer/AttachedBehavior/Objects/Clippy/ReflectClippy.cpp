#include "ReflectClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ReflectClippy* ReflectClippy::create()
{
	ReflectClippy* instance = new ReflectClippy();

	instance->autorelease();

	return instance;
}

ReflectClippy::ReflectClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

ReflectClippy::~ReflectClippy()
{
}

void ReflectClippy::startDialogue()
{
	this->runDialogue(
		Strings::Menus_Hacking_Abilities_Buffs_Reflect_ReflectClippy::create()->setStringReplacementVariables(Strings::Menus_Hacking_RegisterEsi::create()),
		SoundResources::Platformer_Entities_Droid_DroidChatter
	);
}
