#pragma once

#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzleSelectMenuBase.h"

class CipherPuzzleMenuUnderflowRuins : public CipherPuzzleSelectMenuBase
{
public:
	static CipherPuzzleMenuUnderflowRuins* getInstance();

protected:
	CipherPuzzleMenuUnderflowRuins();
	~CipherPuzzleMenuUnderflowRuins();

private:
	typedef CipherPuzzleSelectMenuBase super;

	static std::string ChapterSavekey;
	static CipherPuzzleMenuUnderflowRuins* instance;
};
