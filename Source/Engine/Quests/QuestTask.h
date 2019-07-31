#pragma once

#include "Engine/Maps/GameObject.h"

class QuestTask : public GameObject
{
public:
	enum class QuestState
	{
		Untracked,
		Active,
		ActiveThroughSkippable,
		Complete,
	};
	
	void initialize();
	QuestState getQuestState();
	void setQuestState(QuestState questState);
	std::string getQuestLine();
	std::string getQuestName();
	bool isQuestSkippable();

protected:
	QuestTask(GameObject* owner, std::string questLine, std::string quest, bool skippable = false);
	~QuestTask();

	void initializeListeners() override;
	virtual void onLoad(QuestState questState);
	virtual void onStateChange(QuestState questState, QuestState questStatePrevious) = 0;
	virtual void onActivateRunOnce() = 0;
	virtual void enable(bool isSkippable) = 0;
	virtual void disable() = 0;

private:
	typedef GameObject super;

	void skip();

	GameObject* owner;
	std::string questLine;
	std::string quest;
	QuestState questState;
	bool hasRunActivateFunction;
	bool hasLoaded;
	bool isSkippable;
};

