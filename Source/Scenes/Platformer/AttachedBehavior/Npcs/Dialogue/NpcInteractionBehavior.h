#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CollisionObject;
class InteractMenu;
class LocalizedString;
class PlatformerEntity;
class Squally;

class NpcInteractionBehavior : public AttachedBehavior
{
public:
	static NpcInteractionBehavior* create(GameObject* owner);

	struct DialogueOption
	{
		LocalizedString* dialogueOption;
		std::function<void()> onDialogueChosen;

		DialogueOption(LocalizedString* dialogueOption, std::function<void()> onDialogueChosen) : dialogueOption(dialogueOption), onDialogueChosen(onDialogueChosen) { }
	};

	void addDialogueOption(DialogueOption dialogueOption, float priority);

	static const std::string MapKeyAttachedBehavior;

protected:
	NpcInteractionBehavior(GameObject* owner);
	~NpcInteractionBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void chooseOption(int option);
	void showOptions();
	LocalizedString* getOptionString(int index, LocalizedString* optionText);

	PlatformerEntity* entity;
	Squally* squally;

	bool canInteract;
	
	CollisionObject* dialogueCollision;
	InteractMenu* interactMenu;
	cocos2d::Node* stringNode;

	std::vector<std::tuple<DialogueOption, float>> dialogueOptions;
};
