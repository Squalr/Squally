#include "EnrageClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

EnrageClippy* EnrageClippy::create()
{
	EnrageClippy* instance = new EnrageClippy();

	instance->autorelease();

	return instance;
}

EnrageClippy::EnrageClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

EnrageClippy::~EnrageClippy()
{
}


void EnrageClippy::startDialogue()
{
	this->runDialogue(
		Strings::Menus_Hacking_Abilities_Buffs_Enrage_EnrageClippy::create()
			->setStringReplacementVariables(Strings::Menus_Hacking_Abilities_Buffs_Enrage_ReduceEnrage::create()),
		SoundResources::Platformer_Entities_Droid_DroidChatter
	);
}
