#pragma once
#include <string>

class QuestTask;

class QuestEvents
{
public:
	static const std::string EventAdvanceNextQuestTask;
	static const std::string EventSkipQuestTask;

	struct AdvanceNextQuestArgs
	{
		QuestTask* questTask;

		AdvanceNextQuestArgs(QuestTask* questTask) : questTask(questTask) { }
	};

	struct SkipQuestArgs
	{
		QuestTask* questTask;

		SkipQuestArgs(QuestTask* questTask) : questTask(questTask) { }
	};

	static void TriggerAdvanceToNextQuestTask(AdvanceNextQuestArgs args);
	static void TriggerSkipQuestTask(SkipQuestArgs args);
};
