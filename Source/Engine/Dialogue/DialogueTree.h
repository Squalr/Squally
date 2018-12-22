#pragma once
#include <string>
#include <vector>

#include "document.h"

class DialogueTree
{
public:
	static DialogueTree* loadDialogueFromFile(std::string filePath);
	DialogueTree(std::string text, std::vector<std::pair<std::string, DialogueTree*>> children);
	~DialogueTree();

	DialogueTree* getNextDialogue();

	std::string dialogueText;
	std::vector<std::pair<std::string, DialogueTree*>> dialogueChildren;

private:
	enum TextMood
	{
		Normal,
		Calm,
		Angry
	};

	static DialogueTree* loadDialogueFromJson(std::string json);
	static std::string resolveDialogue(rapidjson::GenericObject<true, rapidjson::Value::ValueType>& dialogueObject);
	static std::string resolveDialogue(rapidjson::GenericObject<false, rapidjson::Value::ValueType>& dialogueObject);
};
