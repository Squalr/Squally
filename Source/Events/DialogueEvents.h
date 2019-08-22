#pragma once
#include <string>

namespace cocos2d
{
	class Node;
}

class LocalizedString;

class DialogueEvents
{
public:
	static const std::string EventDialogueOpen;

	struct DialogueOpenArgs
	{
		LocalizedString* dialogue;
		std::function<void()> onDialogueClose;
		cocos2d::Node* leftContentNode;
		cocos2d::Node* rightContentNode;

		DialogueOpenArgs(LocalizedString* dialogue, std::function<void()> onDialogueClose, cocos2d::Node* leftContentNode = nullptr, cocos2d::Node* rightContentNode = nullptr) : dialogue(dialogue), onDialogueClose(onDialogueClose), leftContentNode(leftContentNode), rightContentNode(rightContentNode)
		{
		}
	};

	static void TriggerDialogueOpen(DialogueOpenArgs args);
};
