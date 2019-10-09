#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"
#include "Engine/Dialogue/DialogueSet.h"

class CollisionObject;
class InteractMenu;
class LocalizedString;
class PlatformerEntity;
class Squally;

class NpcDialogueBehavior : public AttachedBehavior
{
public:
	static NpcDialogueBehavior* create(GameObject* owner);

	void setActiveDialogueSet(DialogueSet* dialogueSet, bool showDialogue = true);
	void addDialogueSet(DialogueSet* dialogueSet);
	void removeDialogueSet(DialogueSet* dialogueSet);
	DialogueSet* getMainDialogueSet();

	static const std::string MapKeyAttachedBehavior;

protected:
	NpcDialogueBehavior(GameObject* owner);
	~NpcDialogueBehavior();

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
	DialogueSet* mainDialogueSet;
	DialogueSet* activeDialogueSet;
	std::vector<DialogueSet*> dialogueSets;
	cocos2d::Node* dialogueSetNode;
};
