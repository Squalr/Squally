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

	struct DialogueVisualArgs
	{
		DialogueBox::DialogueDock dialogueDock;
		DialogueBox::DialogueAlignment dialogueAlignment;
		cocos2d::Node* leftContentNode;
		cocos2d::Node* rightContentNode;
		bool bigFont;

		DialogueVisualArgs(DialogueBox::DialogueDock dialogueDock, DialogueBox::DialogueAlignment dialogueAlignment, cocos2d::Node* leftContentNode = nullptr, cocos2d::Node* rightContentNode = nullptr, bool bigFont = false)
		: dialogueDock(dialogueDock), dialogueAlignment(dialogueAlignment), leftContentNode(leftContentNode), rightContentNode(rightContentNode), bigFont(bigFont)
		{
		}
	};

	struct DialogueOpenArgs
	{
		LocalizedString* dialogue;
		DialogueVisualArgs visualArgs;
		std::function<void()> onDialogueClose;
		bool unhijack;
		bool allowSpace;

		DialogueOpenArgs(LocalizedString* dialogue, DialogueVisualArgs visualArgs, std::function<void()> onDialogueClose, bool unhijack = true, bool allowSpace = true)
			: dialogue(dialogue), visualArgs(visualArgs), onDialogueClose(onDialogueClose), unhijack(unhijack), allowSpace(allowSpace)
		{
		}
	};

	static void TriggerDialogueOpen(DialogueOpenArgs args);
	static void TriggerDialogueClose();
	static cocos2d::Node* BuildPreviewNode(PlatformerEntity* entity, bool isFlipped);
};
