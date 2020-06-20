#pragma once

#include "Engine/Quests/QuestTask.h"

class Portal;
class QuestLine;

class LowerRope : public QuestTask
{
public:
	static LowerRope* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	LowerRope(GameObject* owner, QuestLine* questLine);
	virtual ~LowerRope();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	static const std::string TagRopePortal;
	static const std::string TagRope;
};
