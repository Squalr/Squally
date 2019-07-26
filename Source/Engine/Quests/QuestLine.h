#pragma once

#include "Engine/SmartNode.h"

class QuestTask;

class QuestLine : public SmartNode
{
public:
	void advanceNextQuest(QuestTask* currentQuest);
	void advanceToQuest(std::string questName);
	void markComplete();

protected:
	QuestLine(std::string questLine, std::vector<QuestTask*> questTasks);
	~QuestLine();
	
	void onEnterTransitionDidFinish() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	std::string questLine;
	std::vector<QuestTask*> questTasks;

	QuestTask* activeQuestTask;

	static const std::string QuestLineSaveKeyPrefix;
	static const std::string QuestLineSaveKeyComplete;
};

