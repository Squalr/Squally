#pragma once

#include "Engine/Quests/QuestLine.h"

class OpenCryptLine : public QuestLine
{
public:
	static OpenCryptLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	OpenCryptLine();
	virtual ~OpenCryptLine();

private:
	typedef QuestLine super;
};
