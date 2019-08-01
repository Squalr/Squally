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

protected:
	QuestTask(GameObject* owner, QuestLine* questLine, std::string questTask, std::string questTag, bool skippable = false);
	~QuestTask();

	void initializeListeners() override;
	void onEnterTransitionDidFinish() override;

	virtual void onLoad(QuestState questState) = 0;
	virtual void onActivate(bool isActiveThroughSkippable) = 0;
	virtual void onComplete() = 0;

private:
	typedef GameObject super;
	
	void updateState();
	void complete();

	GameObject* owner;
	QuestLine* questLine;
	std::string questTask;
	std::string questTag;
	QuestState questState;
	bool isSkippable;
};

