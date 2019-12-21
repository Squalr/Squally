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

	struct DialogueCloseArgs
	{
		std::function<void()> onCloseCallback;

		DialogueCloseArgs(std::function<void()> onCloseCallback) : onCloseCallback(onCloseCallback)
		{
		}
	};

	struct DialogueVisualArgs
	{
		DialogueBox::DialogueDock dialogueDock;
		DialogueBox::DialogueAlignment dialogueAlignment;
		std::function<cocos2d::Node*()> leftContentNode;
		std::function<cocos2d::Node*()> rightContentNode;
		bool bigFont;

		DialogueVisualArgs(DialogueBox::DialogueDock dialogueDock, DialogueBox::DialogueAlignment dialogueAlignment, std::function<cocos2d::Node*()> leftContentNode = nullptr, std::function<cocos2d::Node*()> rightContentNode = nullptr, bool bigFont = false)
		: dialogueDock(dialogueDock), dialogueAlignment(dialogueAlignment), leftContentNode(leftContentNode), rightContentNode(rightContentNode), bigFont(bigFont)
		{
		}
	};

	struct DialogueOpenArgs
	{
		LocalizedString* dialogue;
		DialogueVisualArgs visualArgs;
		std::function<void()> onDialogueClose;
		std::string soundResource;
		bool unhijack;
		bool allowSpace;

		DialogueOpenArgs(LocalizedString* dialogue, DialogueVisualArgs visualArgs, std::function<void()> onDialogueClose, std::string soundResource, bool unhijack = true, bool allowSpace = true)
			: dialogue(dialogue), visualArgs(visualArgs), onDialogueClose(onDialogueClose), soundResource(soundResource), unhijack(unhijack), allowSpace(allowSpace)
		{
		}
	};

	static void TriggerOpenDialogue(DialogueOpenArgs args);
	static void TriggerTryDialogueClose(DialogueCloseArgs args);
	static std::function<cocos2d::Node*()> BuildPreviewNode(void* entity, bool isFlipped);
};
