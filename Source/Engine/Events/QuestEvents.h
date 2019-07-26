#pragma once
#include <string>

class Quest;

class QuestEvents
{
public:
	static const std::string EventAdvanceNextQuest;
	static const std::string EventAdvanceQuest;

	struct AdvanceNextQuestArgs
	{
		Quest* quest;

		AdvanceNextQuestArgs(Quest* quest) : quest(quest) { }
	};

	struct AdvanceToQuestArgs
	{
		std::string questLine;
		std::string newQuest;

		AdvanceToQuestArgs(std::string questLine, std::string newQuest) : questLine(questLine), newQuest(newQuest) { }
	};

	static void TriggerAdvanceToNextQuest(AdvanceNextQuestArgs args);
	static void TriggerAdvanceToQuest(AdvanceToQuestArgs args);
};
