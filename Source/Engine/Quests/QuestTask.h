#pragma once

#include "Engine/Maps/GameObject.h"

class QuestTask : public GameObject
{
public:
	virtual void setActive(bool isActive);
	virtual void setActiveThroughSkippable();
	virtual void markComplete();
	std::string getQuestName();
	bool isQuestComplete();
	bool isQuestActive();
	bool isQuestSkippable();

protected:
	QuestTask(GameObject* owner, std::string quest, bool skippable = false);
	~QuestTask();

	void onEnterTransitionDidFinish() override;
	void initializeListeners() override;
	virtual void onLoad(bool isQuestActive, bool isQuestActiveAsSkippable, bool isQuestComplete) = 0;
	virtual void onActivate() = 0;
	virtual void onActivateAsSkippable();

private:
	typedef GameObject super;

	GameObject* owner;
	std::string quest;
	bool isComplete;
	bool isActive;
	bool isSkippable;
	bool hasActivated;
};

