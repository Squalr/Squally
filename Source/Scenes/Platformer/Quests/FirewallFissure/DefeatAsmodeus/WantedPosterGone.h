#pragma once

#include "Engine/Quests/QuestTask.h"

class QueenElise;
class QuestLine;
class Squally;

class WantedPosterGone : public QuestTask
{
public:
	static WantedPosterGone* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	WantedPosterGone(GameObject* owner, QuestLine* questLine);
	virtual ~WantedPosterGone();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void setPostText();

	Squally* squally = nullptr;
	QueenElise* queenElise = nullptr;
};
