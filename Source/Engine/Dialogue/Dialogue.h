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

	void setDialogueSpeed(float speed);
	bool showNextDialogue();

	Label* label;

private:
	static Dialogue* create(DialogueTree* root, std::string fontResource);

	Dialogue(DialogueTree* root, std::string fontResource);
	~Dialogue();

	void onEnter() override;
	void updateLabels();
	void runTypeWriterEffect();

	float dialogueSpeed;
	DialogueTree* dialogueRoot;
	DialogueTree* currentDialogue;

	static const std::string ScheduleKeyTypeWriterEffect;
	static const float DefaultTypeSpeed;
};
