#pragma once
#include <string>

class CipherPuzzleData;

class CipherEvents
{
public:
	static const std::string EventLoadCipher;
	static const std::string EventOpenCipher;

	struct CipherLoadArgs
	{
		std::string cipherName;

		CipherLoadArgs(std::string cipherName) : cipherName(cipherName)
		{
		}
	};

	struct CipherOpenArgs
	{
		CipherPuzzleData* cipherPuzzleData;

		CipherOpenArgs(CipherPuzzleData* cipherPuzzleData) : cipherPuzzleData(cipherPuzzleData)
		{
		}
	};

	static void TriggerLoadCipher(CipherLoadArgs args);
	static void TriggerOpenCipher(CipherOpenArgs args);
};
