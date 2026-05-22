#pragma once

#include <functional>
#include <string>

class CipherPuzzleData;

class CipherPuzzleRegistry
{
public:
	static const std::string EfConnectA;

	static CipherPuzzleData* createPuzzleData(
		const std::string& puzzleKey,
		std::function<void(CipherPuzzleData*)> onUnlock);

private:
	static CipherPuzzleData* createEfConnectA(std::function<void(CipherPuzzleData*)> onUnlock);
};
