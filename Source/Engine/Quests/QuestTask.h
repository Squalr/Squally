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

	static void SaveQuestSaveState(std::string questLine, std::string questTask, std::string key, cocos2d::Value value);
	static cocos2d::Value GetQuestSaveStateOrDefault(std::string questLine, std::string questTask, std::string key, cocos2d::Value value);
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
	void waiveQuestPrereq();
	bool isActive();
	void complete();

	void saveQuestSaveState(std::string key, cocos2d::Value value);
	cocos2d::Value getQuestSaveStateOrDefault(std::string key, cocos2d::Value value);
	
	GameObject* owner;
	QuestLine* questLine;

private:
	typedef GameObject super;
	
	void updateState();

	std::string questTask;
	QuestState questState;
	bool isSkippable;
	bool hasLoaded;
	bool completeCalled;
};

