#pragma once
#include <functional>
#include <string>

#include "cocos/math/CCGeometry.h"

#include "Engine/SmartNode.h"

class DialogueTree;
class LocalizedLabel;

class DialogueLabel : public SmartNode
{
public:
	static DialogueLabel* create(std::string filePath, LocalizedLabel* label, cocos2d::Size size);

	void setDialogueSpeed(float speed);
	bool showNextDialogue();
	void setDialogueShownCallback(std::function<void()> callback);

	LocalizedLabel* label;

private:
	DialogueLabel(DialogueTree* root, LocalizedLabel* label, cocos2d::Size size);
	virtual ~DialogueLabel();

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
