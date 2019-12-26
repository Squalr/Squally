#pragma once

#include "Engine/Maps/GameObject.h"

class QuestLine;

class QuestTask : public GameObject
{
public:
	enum class QuestState
	{
		None,
		Active,
		ActiveThroughSkippable,
		Complete,
	};

	std::string getQuestTaskName();

protected:
	QuestTask(GameObject* owner, QuestLine* questLine, std::string questTask, bool skippable = false);
	~QuestTask();

	void initializeListeners() override;
	void onEnterTransitionDidFinish() override;

	virtual void onLoad(QuestState questState) = 0;
	virtual void onActivate(bool isActiveThroughSkippable) = 0;
	virtual void onComplete() = 0;
	virtual void onSkipped() = 0;
	bool isActive();
	void complete();

private:
	typedef GameObject super;
	
	void updateState();

	GameObject* owner;
	QuestLine* questLine;
	std::string questTask;
	QuestState questState;
	bool isSkippable;
	bool hasLoaded;
	bool completeCalled;
};

