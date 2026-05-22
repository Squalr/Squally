#include "CipherPuzzleRegistry.h"

#include <tuple>
#include <vector>

#include "Scenes/Cipher/CipherPuzzleData.h"

const std::string CipherPuzzleRegistry::EfConnectA = "ef-connect-a";

CipherPuzzleData* CipherPuzzleRegistry::createPuzzleData(
	const std::string& puzzleKey,
	std::function<void(CipherPuzzleData*)> onUnlock)
{
	if (puzzleKey == CipherPuzzleRegistry::EfConnectA)
	{
		return CipherPuzzleRegistry::createEfConnectA(onUnlock);
	}

	return nullptr;
}

CipherPuzzleData* CipherPuzzleRegistry::createEfConnectA(std::function<void(CipherPuzzleData*)> onUnlock)
{
	return CipherPuzzleData::create(
		std::vector<std::tuple<unsigned char, unsigned char>>
		{
			std::make_tuple((unsigned char)('m'), (unsigned char)('m')),
			std::make_tuple((unsigned char)('a'), (unsigned char)('a')),
			std::make_tuple((unsigned char)('g'), (unsigned char)('g')),
			std::make_tuple((unsigned char)('e'), (unsigned char)('e')),
		},
		std::vector<std::string>{},
		"ascii",
		"connect",
		onUnlock
	);
}
