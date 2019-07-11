#pragma once

#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzleSelectMenuBase.h"

class CipherPuzzleMenuEndianForest : public CipherPuzzleSelectMenuBase
{
public:
	static CipherPuzzleMenuEndianForest* getInstance();

protected:
	CipherPuzzleMenuEndianForest();
	~CipherPuzzleMenuEndianForest();

private:
	typedef CipherPuzzleSelectMenuBase super;

	static std::string ChapterSavekey;
	static CipherPuzzleMenuEndianForest* instance;
};
