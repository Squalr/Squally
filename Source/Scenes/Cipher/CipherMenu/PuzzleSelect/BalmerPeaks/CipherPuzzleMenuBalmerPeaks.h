#pragma once

#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzleSelectMenuBase.h"

class CipherPuzzleMenuBalmerPeaks : public CipherPuzzleSelectMenuBase
{
public:
	static void registerGlobalScene();

protected:
	CipherPuzzleMenuBalmerPeaks();
	~CipherPuzzleMenuBalmerPeaks();

private:
	typedef CipherPuzzleSelectMenuBase super;

	static std::string ChapterSavekey;
	static CipherPuzzleMenuBalmerPeaks* instance;
};
