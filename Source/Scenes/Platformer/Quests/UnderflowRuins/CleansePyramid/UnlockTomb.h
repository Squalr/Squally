#pragma once

#include "Engine/Quests/QuestTask.h"

class QuestLine;

class UnlockTomb : public QuestTask
{
public:
	static UnlockTomb* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	UnlockTomb(GameObject* owner, QuestLine* questLine);
	virtual ~UnlockTomb();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	static const std::string TagTombDoor;
	static const std::string TagTorchLeft;
	static const std::string TagTorchRight;
};
