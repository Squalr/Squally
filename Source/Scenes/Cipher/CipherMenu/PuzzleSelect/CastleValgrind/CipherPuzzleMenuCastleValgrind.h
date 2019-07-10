#pragma once

#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzleSelectMenuBase.h"

class CipherPuzzleMenuCastleValgrind : public CipherPuzzleSelectMenuBase
{
public:
	static CipherPuzzleMenuCastleValgrind* getInstance();

protected:
	CipherPuzzleMenuCastleValgrind();
	~CipherPuzzleMenuCastleValgrind();

private:
	typedef CipherPuzzleSelectMenuBase super;

	static std::string ChapterSavekey;
	static CipherPuzzleMenuCastleValgrind* instance;
};
