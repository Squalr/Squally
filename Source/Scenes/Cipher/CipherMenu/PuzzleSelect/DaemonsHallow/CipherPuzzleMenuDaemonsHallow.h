#pragma once

#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzleSelectMenuBase.h"

class CipherPuzzleMenuDaemonsHallow : public CipherPuzzleSelectMenuBase
{
public:
	static CipherPuzzleMenuDaemonsHallow* getInstance();

protected:
	CipherPuzzleMenuDaemonsHallow();
	~CipherPuzzleMenuDaemonsHallow();

private:
	typedef CipherPuzzleSelectMenuBase super;

	static std::string ChapterSavekey;
	static CipherPuzzleMenuDaemonsHallow* instance;
};
