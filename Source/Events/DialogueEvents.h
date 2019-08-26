#pragma once
#include <string>

#include "Engine/Dialogue/DialogueBox.h"

namespace cocos2d
{
	class Node;
}

class LocalizedString;
class PlatformerEntity;

class DialogueEvents
{
public:
	static const std::string EventDialogueOpen;

	struct DialogueOpenArgs
	{
		LocalizedString* dialogue;
		DialogueBox::DialogueDock dialogueDock;
		DialogueBox::DialogueAlignment dialogueAlignment;
		std::function<void()> onDialogueClose;
		cocos2d::Node* leftContentNode;
		cocos2d::Node* rightContentNode;

		DialogueOpenArgs(LocalizedString* dialogue, DialogueBox::DialogueDock dialogueDock, DialogueBox::DialogueAlignment dialogueAlignment, std::function<void()> onDialogueClose, cocos2d::Node* leftContentNode = nullptr, cocos2d::Node* rightContentNode = nullptr)
			: dialogue(dialogue), dialogueDock(dialogueDock), dialogueAlignment(dialogueAlignment), onDialogueClose(onDialogueClose), leftContentNode(leftContentNode), rightContentNode(rightContentNode)
		{
		}
	};

	static void TriggerDialogueOpen(DialogueOpenArgs args);
	static cocos2d::Node* BuildPreviewNode(PlatformerEntity* entity, bool isFlipped);
};
