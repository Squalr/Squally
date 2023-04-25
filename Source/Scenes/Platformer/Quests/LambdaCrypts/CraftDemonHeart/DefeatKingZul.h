#pragma once

#include "Engine/Quests/QuestTask.h"

class KingZul;
class QuestLine;
class ScreamingDoor;
class Squally;
class WorldSound;

class DefeatKingZul : public QuestTask
{
public:
	static DefeatKingZul* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	DefeatKingZul(GameObject* owner, QuestLine* questLine);
	virtual ~DefeatKingZul();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	KingZul* kingZul = nullptr;
	Squally* squally = nullptr;
};
