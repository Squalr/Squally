#include "Dialogue.h"

#include "cocos/2d/CCLabel.h"

#include "Engine/Dialogue/DialogueTree.h"
#include "Engine/Localization/Localization.h"
#include "Events/DialogEvents.h"

using namespace cocos2d;

const std::string Dialogue::ScheduleKeyTypeWriterEffect = "SCHEDULE_TYPE_WRITER_EFFECT";
const float Dialogue::DefaultTypeSpeed = 0.04f;

Dialogue* Dialogue::create(std::string filePath, std::string fontResource, Size size)
{
	Dialogue* instance = new Dialogue(DialogueTree::loadDialogueFromFile(filePath), fontResource, size);

	instance->autorelease();

	return instance;
}

Dialogue::Dialogue(DialogueTree* root, std::string fontResource, Size size)
{
	this->hasStarted = false;
	this->dialogueShownCallback = nullptr;
	this->dialogueRoot = root;
	this->currentDialogue = this->dialogueRoot;
	this->dialogueSpeed = Dialogue::DefaultTypeSpeed;
	this->label = Label::createWithTTF("", fontResource, Localization::getFontSizeH2(fontResource));

	this->label->setHorizontalAlignment(TextHAlignment::LEFT);
	this->label->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->label->enableWrap(true);
	this->label->setDimensions(size.width, size.height);
	this->label->setLineSpacing(8.0f);

	this->addChild(this->label);
}

Dialogue::~Dialogue()
{
	delete(this->dialogueRoot);
}

void Dialogue::setDialogueShownCallback(std::function<void()> callback)
{
	this->dialogueShownCallback = callback;
}

void Dialogue::setDialogueSpeed(float speed)
{
	this->dialogueSpeed = speed;
}

bool Dialogue::showNextDialogue()
{
	if (this->hasStarted)
	{
		this->currentDialogue = this->currentDialogue == nullptr ? nullptr : this->currentDialogue->getNextDialogue();
	}

	this->hasStarted = true;

	if (this->currentDialogue != nullptr)
	{
		this->updateLabels();

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
		mapTypeIdx.insert(std::pair<Label*, int>(this->label, 0));
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

	// TODO: It would be cool to introduce some delay upon encountering a period. Of course w/ localization, this may be a unicode period (ie japanese)
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

			if (this->dialogueShownCallback != nullptr)
			{
				this->dialogueShownCallback();
			}
		}

	}, this->dialogueSpeed, max - 1, 0, Dialogue::ScheduleKeyTypeWriterEffect);
}
