#pragma once

#include "Engine/Quests/QuestTask.h"

namespace cocos2d
{
	class Sprite;
}

class IOU;
class QuestLine;

class FirstIOUFound : public QuestTask
{
public:
	static FirstIOUFound* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	FirstIOUFound(GameObject* owner, QuestLine* questLine, std::string questTag);
	~FirstIOUFound();

	/*
	void onStateChange(QuestTask::QuestState questState, QuestTask::QuestState questStatePrevious) override;
	void onActivateRunOnce() override;
	void enable(bool isSkippable) override;
	void disable() override;
	*/

private:
	typedef QuestTask super;

	void runNotification();

	bool hasRunEvent;
	IOU* iou;
};
