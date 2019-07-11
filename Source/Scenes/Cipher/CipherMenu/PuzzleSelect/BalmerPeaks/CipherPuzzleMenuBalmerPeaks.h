#pragma once

#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzleSelectMenuBase.h"

class CipherPuzzleMenuBalmerPeaks : public CipherPuzzleSelectMenuBase
{
public:
	static CipherPuzzleMenuBalmerPeaks* getInstance();

protected:
	CipherPuzzleMenuBalmerPeaks();
	~CipherPuzzleMenuBalmerPeaks();

private:
	typedef CipherPuzzleSelectMenuBase super;

	static std::string ChapterSavekey;
	static CipherPuzzleMenuBalmerPeaks* instance;
};
