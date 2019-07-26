#pragma once
#include <string>

class QuestTask;

class QuestEvents
{
public:
	static const std::string EventAdvanceNextQuestTask;

	struct AdvanceNextQuestArgs
	{
		QuestTask* questTask;

		AdvanceNextQuestArgs(QuestTask* questTask) : questTask(questTask) { }
	};

	static void TriggerAdvanceToNextQuestTask(AdvanceNextQuestArgs args);
};
