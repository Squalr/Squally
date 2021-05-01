#pragma once

#include <queue>

#include "Engine/Components/Component.h"
#include "Events/DialogueEvents.h"

class DialogueSet;
class InteractMenu;
class InteractObject;
template <class T> class LazyNode;
class LocalizedString;
class PlatformerEntity;
class Scrappy;
class SpeechBubble;

class EntityDialogueBehavior : public Component
{
public:
	static EntityDialogueBehavior* create(GameObject* owner);

	void enqueuePretext(DialogueEvents::DialogueOpenArgs pretext);
	void clearPretext();
	void setActiveDialogueSet(DialogueSet* dialogueSet, bool showDialogue = true);
	void addDialogueSet(DialogueSet* dialogueSet);
	void removeDialogueSet(DialogueSet* dialogueSet);
	DialogueSet* getMainDialogueSet();
	SpeechBubble* getSpeechBubble();

	static const std::string MapKey;

protected:
	EntityDialogueBehavior(GameObject* owner);
	virtual ~EntityDialogueBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef Component super;

	void onInteract();
	void progressDialogue();
	void showOptions();
	bool hasDialogueOptions();
	void updateInteractable();
	LocalizedString* getOptionString(int index, LocalizedString* optionText);
	SpeechBubble* buildSpeechBubble();

	PlatformerEntity* entity;
	Scrappy* scrappy;
	LazyNode<SpeechBubble>* speechBubble;
	InteractObject* dialogueInteraction;

	bool optionsVisible;
	
	std::queue<DialogueEvents::DialogueOpenArgs> pretextQueue;
	DialogueSet* mainDialogueSet;
	DialogueSet* activeDialogueSet;
	std::vector<DialogueSet*> dialogueSets;
	cocos2d::Node* pretextNode;
	cocos2d::Node* dialogueSetNode;
};
