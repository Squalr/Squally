#include "CurseOfTonguesClippy.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Scenes/Platformer/Dialogue/Voices.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CurseOfTonguesClippy* CurseOfTonguesClippy::create()
{
	CurseOfTonguesClippy* instance = new CurseOfTonguesClippy();

	instance->autorelease();

	return instance;
}

CurseOfTonguesClippy::CurseOfTonguesClippy() : super()
{
	this->clippyAnimations = SmartAnimationNode::create(EntityResources::Helpers_EndianForest_Scrappy_Animations);

	this->clippyAnimations->setFlippedX(true);

	this->animationNode->addChild(this->clippyAnimations);
}

CurseOfTonguesClippy::~CurseOfTonguesClippy()
{
}

void CurseOfTonguesClippy::startDialogue()
{
	this->runDialogue(
		Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTongues_CurseOfTonguesClippy::create()
			->setStringReplacementVariables(Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTongues_ReduceCurse::create()),
		Voices::GetNextVoiceMedium(Voices::VoiceType::Droid)
	);
}
