#pragma once
#include <map>

#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"

class CipherPuzzleRot13 : public CipherPuzzleData
{
public:
	static CipherPuzzleRot13* create();

	static const std::string MapKeyRot13;

private:
	typedef CipherPuzzleData super;
	CipherPuzzleRot13();
	~CipherPuzzleRot13();
};
