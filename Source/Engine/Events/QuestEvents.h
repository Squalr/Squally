#pragma once
#include <string>

class QuestTask;

class QuestEvents
{
public:
	static const std::string EventAdvanceNextQuestTask;
	static const std::string EventAdvanceQuestTask;

	struct AdvanceNextQuestArgs
	{
		QuestTask* questTask;

		AdvanceNextQuestArgs(QuestTask* questTask) : questTask(questTask) { }
	};

	struct AdvanceToQuestArgs
	{
		std::string questLine;
		std::string newQuestTask;

		AdvanceToQuestArgs(std::string questLine, std::string newQuestTask) : questLine(questLine), newQuestTask(newQuestTask) { }
	};

	static void TriggerAdvanceToNextQuestTask(AdvanceNextQuestArgs args);
	static void TriggerAdvanceToQuestTask(AdvanceToQuestArgs args);
};
