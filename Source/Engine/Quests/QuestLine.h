#pragma once

#include "Engine/SmartNode.h"

class QuestTask;

class QuestLine : public SmartNode
{
public:
	void advanceNextQuest(QuestTask* currentQuest);
	void markComplete();

protected:
	QuestLine(std::string questLine, std::string quest, std::string questTag, std::vector<QuestTask*> questTasks);
	~QuestLine();
	
	void onEnterTransitionDidFinish() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	QuestTask* getActiveQuest();

	std::string questLine;
	std::string quest;
	std::string questTag;
	std::vector<QuestTask*> questTasks;

	QuestTask* trackedQuestTask;

	static const std::string QuestLineSaveKeyPrefix;
	static const std::string QuestLineSaveKeyComplete;
};

