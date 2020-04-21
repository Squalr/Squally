#include "FireballClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

FireballClippy* FireballClippy::create()
{
	FireballClippy* instance = new FireballClippy();

	instance->autorelease();

	return instance;
}

FireballClippy::FireballClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

FireballClippy::~FireballClippy()
{
}

void FireballClippy::startDialogue()
{
	this->runDialogue(Strings::Menus_Hacking_Objects_Combat_Projectiles_Fireball_ApplySpeed_FireballClippy::create()
		->setStringReplacementVariables(Strings::Menus_Hacking_Objects_Combat_Projectiles_Fireball_ApplySpeed_StopFireball::create()),
		SoundResources::Platformer_Entities_Droid_DroidChatter
	);
}
