#include "DialogueTree.h"

#include "allocators.h"
#include "encodings.h"
#include "stringbuffer.h"
#include "writer.h"

#include "Engine/Localization/Localization.h"
#include "Events/DialogEvents.h"

// Windows is fucking stupid and has GetObject defined in some GDI macro, this is the workaround
#pragma push_macro("GetObject")
#undef GetObject

using namespace cocos2d;
using namespace rapidjson;

DialogueTree * DialogueTree::loadDialogueFromFile(std::string filePath)
{
	return DialogueTree::loadDialogueFromJson(FileUtils::getInstance()->getStringFromFile(filePath.c_str()));
}

DialogueTree * DialogueTree::loadDialogueFromJson(std::string json)
{
	Document document = Document();
	document.Parse<0>(json.c_str());

	std::string dialogueText = "";

	if (document.HasMember("Dialogue"))
	{
		GenericObject<false, rapidjson::Value::ValueType> dialogueObject = document["Dialogue"].GetObject();
		dialogueText = DialogueTree::resolveDialogue(&dialogueObject);
	}

	std::vector<std::pair<std::string, DialogueTree*>>* children = new std::vector<std::pair<std::string, DialogueTree*>>();

	if (document.HasMember("Links"))
	{
		GenericArray<false, rapidjson::Value::ValueType> choicesArray = document["Links"].GetArray();

		// Iterate through choices
		for (rapidjson::Value::ConstValueIterator choiceIterator = choicesArray.Begin(); choiceIterator != choicesArray.End(); ++choiceIterator)
		{
			std::string choiceText = "";
			DialogueTree* child = nullptr;

			// Parse the choice object
			for (auto member = choiceIterator->MemberBegin(); member != choiceIterator->MemberEnd(); ++member)
			{
				std::string field = member->name.GetString();

				if (field == "Choice")
				{
					GenericObject<true, rapidjson::Value::ValueType> choiceObject = member->value.GetObject();
					choiceText = DialogueTree::resolveDialogue(&choiceObject);
				}

				if (field == "Node")
				{
					auto value = member->value.GetObject();

					rapidjson::StringBuffer stringBuffer;
					rapidjson::Writer<rapidjson::StringBuffer> writer(stringBuffer);
					member->value.Accept(writer);
					std::string childString = stringBuffer.GetString();

					child = DialogueTree::loadDialogueFromJson(childString);
				}
			}

			if (child != nullptr)
			{
				children->push_back(std::pair<std::string, DialogueTree*>(choiceText, child));
			}
		}
	}

	DialogueTree* dialog = new DialogueTree(dialogueText, children);

	return dialog;
}

DialogueTree::DialogueTree(std::string text, std::vector<std::pair<std::string, DialogueTree*>>* children)
{
	this->dialogueText = text;
	this->dialogueChildren = children;
}

DialogueTree::~DialogueTree()
{
	if (this->dialogueChildren != nullptr)
	{
		for (auto it = this->dialogueChildren->begin(); it != this->dialogueChildren->end(); it++)
		{
			delete((*it).second);
		}

		delete(this->dialogueChildren);
	}
}

std::string DialogueTree::resolveDialogue(GenericObject<true, rapidjson::Value::ValueType>* dialogueObject)
{
	std::string languageCode = Localization::getLanguageCode();

	for (auto it = dialogueObject->begin(); it != dialogueObject->end(); it++)
	{
		if (it->name.GetString() == languageCode)
		{
			return it->value.GetString();
		}
	}

	return "";
}

std::string DialogueTree::resolveDialogue(GenericObject<false, rapidjson::Value::ValueType>* dialogueObject)
{
	std::string languageCode = Localization::getLanguageCode();

	for (auto it = dialogueObject->begin(); it != dialogueObject->end(); it++)
	{
		if (it->name.GetString() == languageCode)
		{
			return it->value.GetString();
		}
	}

	return "";
}

DialogueTree* DialogueTree::getNextDialogue()
{
	DialogueTree* dialogueTree = nullptr;

	if (dialogueChildren->size() == 1)
	{
		dialogueTree = (*this->dialogueChildren)[0].second;
	}

	return dialogueTree;
}

#pragma pop_macro("GetObject")
