#include "SpeechBubble.h"

#include "cocos/2d/CCLabel.h"

#include "Engine/Dialogue/DialogueTree.h"
#include "Engine/Localization/Localization.h"
#include "Events/DialogEvents.h"

using namespace cocos2d;

SpeechBubble* SpeechBubble::create()
{
	SpeechBubble* instance = new SpeechBubble();

	instance->autorelease();

	return instance;
}

SpeechBubble::SpeechBubble()
{
}

SpeechBubble::~SpeechBubble()
{
}