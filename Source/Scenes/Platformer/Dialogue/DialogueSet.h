#pragma once

#include "Engine/SmartNode.h"
#include "Events/DialogueEvents.h"

class DialogueOption;

class DialogueSet : public SmartNode
{
public:
	static DialogueSet* create(DialogueEvents::DialogueVisualArgs args);

	DialogueOption* addDialogueOption(DialogueOption* dialogueOption, float priority);
	void removeDialogueOption(DialogueOption* dialogueOption);
	std::vector<std::tuple<DialogueOption*, float>> getDialogueOptions();
	DialogueEvents::DialogueVisualArgs getArgs();

protected:
	DialogueSet(DialogueEvents::DialogueVisualArgs args);
	virtual ~DialogueSet();

private:
	typedef SmartNode super;

	DialogueEvents::DialogueVisualArgs args;
	cocos2d::Node* optionsNode;

	std::vector<std::tuple<DialogueOption*, float>> dialogueOptions;
};
