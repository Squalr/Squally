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
	static const std::string EventDialogueClose;

	struct DialogueOpenArgs
	{
		LocalizedString* dialogue;
		DialogueBox::DialogueDock dialogueDock;
		DialogueBox::DialogueAlignment dialogueAlignment;
		std::function<void()> onDialogueClose;
		cocos2d::Node* leftContentNode;
		cocos2d::Node* rightContentNode;
		bool unhijack;

		DialogueOpenArgs(LocalizedString* dialogue, DialogueBox::DialogueDock dialogueDock, DialogueBox::DialogueAlignment dialogueAlignment, std::function<void()> onDialogueClose, cocos2d::Node* leftContentNode = nullptr, cocos2d::Node* rightContentNode = nullptr, bool unhijack = true)
			: dialogue(dialogue), dialogueDock(dialogueDock), dialogueAlignment(dialogueAlignment), onDialogueClose(onDialogueClose), leftContentNode(leftContentNode), rightContentNode(rightContentNode), unhijack(unhijack)
		{
		}
	};

	static void TriggerDialogueOpen(DialogueOpenArgs args);
	static void TriggerDialogueClose();
	static cocos2d::Node* BuildPreviewNode(PlatformerEntity* entity, bool isFlipped);
};
