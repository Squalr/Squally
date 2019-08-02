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

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runNotification();

	bool hasRunEvent;
	IOU* iou;
};
