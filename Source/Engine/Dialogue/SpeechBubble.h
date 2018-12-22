#pragma once

#include "Engine/SmartNode.h"

class DialogueTree;

class SpeechBubble : public SmartNode
{
public:
	static SpeechBubble* create();

	void runDialogue(DialogueTree* dialogueTree);

private:
	SpeechBubble();
	virtual ~SpeechBubble();
};
