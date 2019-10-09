#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;

class DialogueSet : public SmartNode
{
public:
	static DialogueSet* create();

	struct DialogueOption
	{
		LocalizedString* dialogueOption;
		std::function<void()> onDialogueChosen;

		DialogueOption(LocalizedString* dialogueOption, std::function<void()> onDialogueChosen) : dialogueOption(dialogueOption), onDialogueChosen(onDialogueChosen) { }
	};

	void addDialogueOption(DialogueOption dialogueOption, float priority);

	std::vector<std::tuple<DialogueOption, float>> dialogueOptions;

protected:
	typedef SmartNode super;

	DialogueSet();
	~DialogueSet();

	void initializePositions() override;
	void initializeListeners() override;

private:
	cocos2d::Node* stringNode;
};
