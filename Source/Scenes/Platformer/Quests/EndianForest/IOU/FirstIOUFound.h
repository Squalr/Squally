#pragma once

#include "Engine/Quests/QuestTask.h"

class IOU;

class FirstIOUFound : public QuestTask
{
public:
	static FirstIOUFound* create(GameObject* owner);

	static const std::string MapKeyQuest;

protected:
	FirstIOUFound(GameObject* owner);
	~FirstIOUFound();

	void onLoad(QuestTask::QuestState questState) override;
	void onStateChange(QuestTask::QuestState questState, QuestTask::QuestState questStatePrevious) override;
	void onActivateRunOnce() override;

private:
	typedef QuestTask super;

	void runNotification();

	bool hasRunEvent;
	IOU* iou;
};
