#pragma once
#include <map>

#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"

class CipherPuzzleAtbash : public CipherPuzzleData
{
public:
	static CipherPuzzleAtbash* create();

	static const std::string MapKeyAtbash;

private:
	typedef CipherPuzzleData super;
	CipherPuzzleAtbash();
	~CipherPuzzleAtbash();
};
