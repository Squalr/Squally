#include "QuestLine.h"

#include "cocos/base/CCValue.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/QuestEvents.h"
#include "Engine/Quests/Quest.h"
#include "Engine/Save/SaveManager.h"

using namespace cocos2d;

const std::string QuestLine::QuestLineSaveKeyPrefix = "SAVE_KEY_QUEST_LINE_";
const std::string QuestLine::QuestLineSaveKeyComplete = "COMPLETE";

QuestLine::QuestLine(std::string questLine, std::vector<Quest*> quests)
{
	this->questLine = questLine;
	this->quests = quests;
	this->activeQuest = quests.size() > 0 ? quests.front() : nullptr;

	std::string savedQuestName = SaveManager::getProfileDataOrDefault(QuestLine::QuestLineSaveKeyPrefix + this->questLine, Value("")).asString();

	for (auto it = this->quests.begin(); it != this->quests.end(); it++)
	{
		if ((*it)->getQuestName() == savedQuestName)
		{
			this->activeQuest = *it;
			break;
		}
	}

	for (auto it = this->quests.begin(); it != this->quests.end(); it++)
	{
		this->addChild(*it);
	}
}

QuestLine::~QuestLine()
{
}

void QuestLine::onEnter()
{
	super::onEnter();

	if (this->activeQuest != nullptr)
	{
		this->activeQuest->activate();
	}
}

void QuestLine::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(QuestEvents::EventAdvanceNextQuest, [=](EventCustom* eventCustom)
	{
		QuestEvents::AdvanceNextQuestArgs* args = static_cast<QuestEvents::AdvanceNextQuestArgs*>(eventCustom->getUserData());
		
		if (args != nullptr && args->quest == this->activeQuest)
		{
			this->advanceNextQuest();
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(QuestEvents::EventAdvanceQuest, [=](EventCustom* eventCustom)
	{
		QuestEvents::AdvanceToQuestArgs* args = static_cast<QuestEvents::AdvanceToQuestArgs*>(eventCustom->getUserData());
		
		if (args != nullptr && args->questLine == this->questLine)
		{
			this->advanceToQuest(args->newQuest);
		}
	}));
}

void QuestLine::advanceNextQuest()
{
	bool takeNext = this->activeQuest == nullptr;

	if (this->activeQuest != nullptr)
	{
		this->activeQuest->deactivate();
	}

	if (this->quests.empty() || this->activeQuest == this->quests.back())
	{
		this->markComplete();
		return;
	}

	for (auto it = this->quests.begin(); it != this->quests.end(); it++)
	{
		if (takeNext)
		{
			this->activeQuest = *it;
			break;
		}

		if ((*it) == this->activeQuest)
		{
			takeNext = true;
		}
	}
	
	if (this->activeQuest != nullptr)
	{
		const std::string questName = this->activeQuest->getQuestName();

		SaveManager::saveProfileData(QuestLine::QuestLineSaveKeyPrefix + this->questLine, Value(questName));

		this->activeQuest->activate();
	}
}

void QuestLine::advanceToQuest(std::string questName)
{
	if (this->activeQuest != nullptr)
	{
		this->activeQuest->deactivate();
	}

	this->activeQuest = nullptr;

	// Advance to the quest with the given name
	for (auto it = this->quests.begin(); it != this->quests.end(); it++)
	{
		const std::string nextQuestName = (*it)->getQuestName();

		if (nextQuestName == questName)
		{
			SaveManager::saveProfileData(QuestLine::QuestLineSaveKeyPrefix + this->questLine, Value(questName));
			this->activeQuest = *it;
			this->activeQuest->activate();
			return;
		}
	}

	// Fail safe
	if (this->activeQuest == nullptr)
	{
		this->markComplete();
	}
}

void QuestLine::markComplete()
{
	this->activeQuest = nullptr;
	SaveManager::saveProfileData(QuestLine::QuestLineSaveKeyPrefix + this->questLine, Value(QuestLine::QuestLineSaveKeyComplete));
}
