#pragma once
#include <string>

class QuestTask;

class QuestEvents
{
public:
	static const std::string EventQuestTaskComplete;

	struct QuestTaskCompleteArgs
	{
		std::string questLine;
		QuestTask* questTask;

		QuestTaskCompleteArgs(std::string questLine, QuestTask* questTask) : questLine(questLine), questTask(questTask) { }
	};

	static void TriggerQuestTaskComplete(QuestTaskCompleteArgs args);
};
