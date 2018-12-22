#include "DialogueLabel.h"

#include "cocos/2d/CCLabel.h"

#include "Engine/Dialogue/DialogueTree.h"
#include "Engine/Localization/Localization.h"
#include "Events/DialogEvents.h"

using namespace cocos2d;

const std::string DialogueLabel::ScheduleKeyTypeWriterEffect = "SCHEDULE_TYPE_WRITER_EFFECT";
const float DialogueLabel::DefaultTypeSpeed = 0.04f;

DialogueLabel* DialogueLabel::create(std::string filePath, std::string fontResource, Size size)
{
	DialogueLabel* instance = new DialogueLabel(DialogueTree::loadDialogueFromFile(filePath), fontResource, size);

	instance->autorelease();

	return instance;
}

DialogueLabel::DialogueLabel(DialogueTree* root, std::string fontResource, Size size)
{
	this->hasStarted = false;
	this->dialogueShownCallback = nullptr;
	this->dialogueRoot = root;
	this->currentDialogue = this->dialogueRoot;
	this->dialogueSpeed = DialogueLabel::DefaultTypeSpeed;
	this->label = Label::createWithTTF("", fontResource, Localization::getFontSizeH2(fontResource));

	this->label->setHorizontalAlignment(TextHAlignment::LEFT);
	this->label->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->label->enableWrap(true);
	this->label->setDimensions(size.width, size.height);
	this->label->setLineSpacing(8.0f);

	this->addChild(this->label);
}

DialogueLabel::~DialogueLabel()
{
	delete(this->dialogueRoot);
}

void DialogueLabel::setDialogueShownCallback(std::function<void()> callback)
{
	this->dialogueShownCallback = callback;
}

void DialogueLabel::setDialogueSpeed(float speed)
{
	this->dialogueSpeed = speed;
}

bool DialogueLabel::showNextDialogue()
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

void DialogueLabel::updateLabels()
{
	if (this->currentDialogue != nullptr)
	{
		this->label->setString(this->currentDialogue->dialogueText);
		this->runTypeWriterEffect();
	}
}

void DialogueLabel::runTypeWriterEffect()
{
	this->label->unschedule(DialogueLabel::ScheduleKeyTypeWriterEffect);

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
			this->label->unschedule(DialogueLabel::ScheduleKeyTypeWriterEffect);
			mapTypeIdx.erase(it);

			if (this->dialogueShownCallback != nullptr)
			{
				this->dialogueShownCallback();
			}
		}

	}, this->dialogueSpeed, max - 1, 0, DialogueLabel::ScheduleKeyTypeWriterEffect);
}
