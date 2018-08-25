#include "Dialogue.h"

Dialogue* Dialogue::loadDialogueFromFile(std::string filePath, std::string fontResource)
{
	return Dialogue::create(DialogueTree::loadDialogueFromFile(filePath), fontResource);
}

Dialogue* Dialogue::create(DialogueTree* root, std::string fontResource)
{
	Dialogue* instance = new Dialogue(root, fontResource);

	instance->autorelease();

	return instance;
}

Dialogue::Dialogue(DialogueTree* root, std::string fontResource)
{
	this->dialogueRoot = root;
	this->currentDialogue = this->dialogueRoot;
	this->label = Label::create("", fontResource, Localization::getFontSizeH2(fontResource));

	this->label->setHorizontalAlignment(TextHAlignment::LEFT);
	this->label->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->updateLabels();

	this->addChild(this->label);
}

Dialogue::~Dialogue()
{
	delete(this->dialogueRoot);
}

bool Dialogue::showNextDialogue()
{
	DialogueTree* next = currentDialogue == nullptr ? nullptr : currentDialogue->getNextDialogue();

	if (next != nullptr)
	{
		return true;
	}

	return false;
}

void Dialogue::updateLabels()
{
	if (this->currentDialogue != nullptr)
	{
		this->label->setString(this->currentDialogue->dialogueText);
	}
}
