#pragma once

#include "Engine/Quests/QuestLine.h"

class RezLazarusLine : public QuestLine
{
public:
	static RezLazarusLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	RezLazarusLine();
	virtual ~RezLazarusLine();

private:
	typedef QuestLine super;
};
