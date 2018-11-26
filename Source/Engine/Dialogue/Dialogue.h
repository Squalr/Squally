#pragma once
#include "cocos2d.h"

#include "Engine/Dialogue/DialogueTree.h"
#include "Engine/Localization/Localization.h"
#include "Engine/SmartNode.h"
#include "Engine/UI/Controls/MenuLabel.h"
#include "Events/DialogEvents.h"

using namespace cocos2d;

class Dialogue : public SmartNode
{
public:
	static Dialogue * create(std::string filePath, std::string fontResource, Size size);

	void setDialogueSpeed(float speed);
	bool showNextDialogue();
	void setDialogueShownCallback(std::function<void()> callback);

	Label* label;

private:
	Dialogue(DialogueTree* root, std::string fontResource, Size size);
	~Dialogue();

	void updateLabels();
	void runTypeWriterEffect();

	bool hasStarted;
	float dialogueSpeed;
	DialogueTree* dialogueRoot;
	DialogueTree* currentDialogue;
	std::function<void()> dialogueShownCallback;

	static const std::string ScheduleKeyTypeWriterEffect;
	static const float DefaultTypeSpeed;
};
