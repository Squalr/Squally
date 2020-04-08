#pragma once

#include "Engine/Quests/QuestTask.h"

class QuestLine;

class FindElrielTelomere : public QuestTask
{
public:
	static FindElrielTelomere* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	FindElrielTelomere(GameObject* owner, QuestLine* questLine);
	virtual ~FindElrielTelomere();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;
};
