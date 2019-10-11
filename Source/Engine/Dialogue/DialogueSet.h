#pragma once

#include "Engine/SmartNode.h"

class DialogueOption;
class LocalizedString;

class DialogueSet : public SmartNode
{
public:
	static DialogueSet* create();

	void addDialogueOption(DialogueOption* dialogueOption, float priority);
	void removeDialogueOption(DialogueOption* dialogueOption);
	std::vector<std::tuple<DialogueOption*, float>> getDialogueOptions();

protected:
	typedef SmartNode super;

	DialogueSet();
	~DialogueSet();

private:
	cocos2d::Node* optionsNode;

	std::vector<std::tuple<DialogueOption*, float>> dialogueOptions;
};
