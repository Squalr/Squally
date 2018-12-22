#pragma once
#include <functional>
#include <string>

#include "cocos/math/CCGeometry.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Label;
}

class DialogueTree;

class DialogueLabel : public SmartNode
{
public:
	static DialogueLabel* create(std::string filePath, std::string fontResource, cocos2d::Size size);

	void setDialogueSpeed(float speed);
	bool showNextDialogue();
	void setDialogueShownCallback(std::function<void()> callback);

	cocos2d::Label* label;

private:
	DialogueLabel(DialogueTree* root, std::string fontResource, cocos2d::Size size);
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
