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
	QuestState getQuestState();

	static QuestState getQuestStateForTask(QuestLine* questLine, std::string questTask);

protected:
	QuestTask(GameObject* owner, QuestLine* questLine, std::string questTask, bool skippable = false);
	virtual ~QuestTask();

	void initializeListeners() override;
	void onEnterTransitionDidFinish() override;

	virtual void onLoad(QuestState questState) = 0;
	virtual void onActivate(bool isActiveThroughSkippable) = 0;
	virtual void onComplete() = 0;
	virtual void onSkipped() = 0;
	bool isActive();
	void complete();

	void saveQuestSaveState(std::string key, cocos2d::Value value);
	cocos2d::Value getQuestSaveStateOrDefault(std::string key, cocos2d::Value value);
	
	QuestLine* questLine;

private:
	typedef GameObject super;
	
	void updateState();

	GameObject* owner;
	std::string questTask;
	QuestState questState;
	bool isSkippable;
	bool hasLoaded;
	bool completeCalled;
};

