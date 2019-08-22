#pragma once
#include <string>

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

	enum class DialogueAlignment
	{
		Left,
		Center,
		Right,
	};

	struct DialogueOpenArgs
	{
		LocalizedString* dialogue;
		DialogueAlignment dialogueAlignment;
		std::function<void()> onDialogueClose;
		cocos2d::Node* leftContentNode;
		cocos2d::Node* rightContentNode;

		DialogueOpenArgs(LocalizedString* dialogue, DialogueAlignment dialogueAlignment, std::function<void()> onDialogueClose, cocos2d::Node* leftContentNode = nullptr, cocos2d::Node* rightContentNode = nullptr)
			: dialogue(dialogue), dialogueAlignment(dialogueAlignment), onDialogueClose(onDialogueClose), leftContentNode(leftContentNode), rightContentNode(rightContentNode)
		{
		}
	};

	static void TriggerDialogueOpen(DialogueOpenArgs args);
	static cocos2d::Node* BuildPreviewNode(PlatformerEntity* entity, bool isFlipped);
};
