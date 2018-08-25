#include "Dialogue.h"

const std::string Dialogue::ScheduleKeyTypeWriterEffect = "TYPE_WRITER_EFFECT";
const float Dialogue::DefaultTypeSpeed = 0.05f;

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
	this->dialogueSpeed = Dialogue::DefaultTypeSpeed;
	this->label = Label::create("", fontResource, Localization::getFontSizeH2(fontResource));

	this->label->setHorizontalAlignment(TextHAlignment::LEFT);
	this->label->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->label);
}

void Dialogue::onEnter()
{
	Node::onEnter();

	this->updateLabels();
}

Dialogue::~Dialogue()
{
	delete(this->dialogueRoot);
}

void Dialogue::setDialogueSpeed(float speed)
{
	this->dialogueSpeed = speed;
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
		this->runTypeWriterEffect();
	}
}

void Dialogue::runTypeWriterEffect()
{
	this->label->unschedule(Dialogue::ScheduleKeyTypeWriterEffect);

	static std::map<Label*, int> mapTypeIdx;
	std::map<Label*, int>::iterator it;
	it = mapTypeIdx.find(this->label);

	if (it == mapTypeIdx.end())
	{
		std::pair<std::map<Label*, int>::iterator, bool> ret = mapTypeIdx.insert(std::pair<Label*, int>(this->label, 0));
		it = mapTypeIdx.find(this->label);
	}
	else
	{
		it->second = 0;
	}

	int max = this->label->getStringLength();

	for (int i = 0; i < max; i++)
	{
		if (this->label->getLetter(i) != nullptr)
		{
			this->label->getLetter(i)->setOpacity(0);
		}
	}

	this->label->schedule([=](float dt)
	{
		if (this->label->getLetter(it->second) != nullptr)
		{
			this->label->getLetter(it->second)->setOpacity(255);
		}
		
		it->second++;

		if (it->second == max)
		{
			this->label->unschedule(Dialogue::ScheduleKeyTypeWriterEffect);
			mapTypeIdx.erase(it);
			//// callback();
		}

	}, this->dialogueSpeed, max - 1, 0, Dialogue::ScheduleKeyTypeWriterEffect);
}
