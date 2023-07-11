#pragma once

#include "Engine/Quests/QuestTask.h"

class CameraStop;
class CollisionObject;
class Perceptron;
class Gecky;
class Guano;
class Mabel;
class QuestLine;
class Scrappy;
class Squally;

class RevealMabel : public QuestTask
{
public:
	static RevealMabel* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	RevealMabel(GameObject* owner, QuestLine* questLine);
	virtual ~RevealMabel();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;
	
	static const std::string MapEventMabelRevealed;
};
