#pragma once

#include "Engine/SmartNode.h"

class Quest;

class QuestLine : public SmartNode
{
public:
	void advanceNextQuest();
	void advanceToQuest(std::string questName);
	void markComplete();

protected:
	QuestLine(std::string questLine, std::vector<Quest*> quests);
	~QuestLine();
	
	void onEnter() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	std::string questLine;
	std::vector<Quest*> quests;

	Quest* activeQuest;

	static const std::string QuestLineSaveKeyPrefix;
	static const std::string QuestLineSaveKeyComplete;
};

