#pragma once
#include "cocos2d.h"

#include "Engine/Dialogue/DialogueTree.h"
#include "Engine/Localization/Localization.h"
#include "Engine/Rendering/Components/MenuLabel.h"
#include "Events/DialogEvents.h"
#include "Resources.h"

using namespace cocos2d;

class Dialogue : public Node
{
public:
	static Dialogue * loadDialogueFromFile(std::string filePath, std::string fontResource);

	bool showNextDialogue();

	Label* label;

private:
	static Dialogue* create(DialogueTree* root, std::string fontResource);

	Dialogue(DialogueTree* root, std::string fontResource);
	~Dialogue();

	void updateLabels();

	DialogueTree* dialogueRoot;
	DialogueTree* currentDialogue;
};
