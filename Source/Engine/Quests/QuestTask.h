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
	std::string getQuestName();
	bool isQuestSkippable();

protected:
	QuestTask(GameObject* owner, std::string quest, bool skippable = false);
	~QuestTask();

	void initializeListeners() override;
	virtual void onLoad(QuestState questState) = 0;
	virtual void onStateChange(QuestState questState, QuestState questStatePrevious) = 0;
	virtual void onActivateRunOnce() = 0;

private:
	typedef GameObject super;

	GameObject* owner;
	std::string quest;
	QuestState questState;
	bool hasRunActivateFunction;
	bool hasLoaded;
	bool isSkippable;
};

