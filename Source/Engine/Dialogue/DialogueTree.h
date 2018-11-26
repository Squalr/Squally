#pragma once
#include "cocos2d.h"
#include "allocators.h"
#include "encodings.h"
#include "document.h"
#include "stringbuffer.h"
#include "writer.h"

#include "Engine/Localization/Localization.h"
#include "Events/DialogEvents.h"

using namespace cocos2d;
using namespace rapidjson;

class DialogueTree
{
public:
	static DialogueTree * loadDialogueFromFile(std::string filePath);
	DialogueTree(std::string text, std::vector<std::pair<std::string, DialogueTree*>>* children);
	~DialogueTree();

	DialogueTree* getNextDialogue();

	std::string dialogueText;
	std::vector<std::pair<std::string, DialogueTree*>>* dialogueChildren;

private:
	enum TextMood
	{
		Normal,
		Calm,
		Angry
	};

	static DialogueTree * loadDialogueFromJson(std::string json);
	static std::string resolveDialogue(GenericObject<true, rapidjson::Value::ValueType>* dialogueObject);
	static std::string resolveDialogue(GenericObject<false, rapidjson::Value::ValueType>* dialogueObject);
};
