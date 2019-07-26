#pragma once

#include "Engine/Quests/Quest.h"

class HelpSquallyHeal : public Quest
{
public:
	static HelpSquallyHeal* create();

	static const std::string MapKeyQuest;

protected:
	HelpSquallyHeal();
	~HelpSquallyHeal();

private:
	typedef Quest super;
	void initializeListeners() override;
};

