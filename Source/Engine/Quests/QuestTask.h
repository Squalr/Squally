#pragma once

#include "Engine/Maps/GameObject.h"

class QuestLine;

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

protected:
	QuestTask(GameObject* owner, QuestLine* questLine, std::string questTask, std::string questTag, bool skippable = false);
	~QuestTask();

	void initializeListeners() override;

private:
	typedef GameObject super;
	
	void updateState();
	/*
	void initialize();
	virtual void onLoad(QuestState questState);
	virtual void onStateChange(QuestState questState, QuestState questStatePrevious) = 0;
	virtual void onActivateRunOnce() = 0;
	virtual void enable(bool isSkippable) = 0;
	virtual void disable() = 0;
	QuestState getQuestState();
	void setQuestState(QuestState questState);
	std::string getQuestLine();
	std::string getQuestName();
	bool isQuestSkippable();
	void skip();
	*/

	GameObject* owner;
	QuestLine* questLine;
	std::string questTask;
	std::string questTag;
	QuestState questState;
	bool isSkippable;
};

