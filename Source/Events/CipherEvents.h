#pragma once
#include <functional>
#include <string>

#include "cocos/math/CCGeometry.h"

class BlockBase;
class CipherPuzzleData;

class CipherEvents
{
public:
	static const std::string EventLoadCipher;
	static const std::string EventOpenCipher;
	static const std::string EventRequestToolSpawn;
	static const std::string EventShowAsciiTable;

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

	struct CipherSpawnArgs
	{
		std::function<BlockBase*()> spawnBlockFunc;
		cocos2d::Vec2 spawnCoords;

		CipherSpawnArgs(std::function<BlockBase*()> spawnBlockFunc, cocos2d::Vec2 spawnCoords) : spawnBlockFunc(spawnBlockFunc), spawnCoords(spawnCoords)
		{
		}
	};

	static void TriggerLoadCipher(CipherLoadArgs args);
	static void TriggerOpenCipher(CipherOpenArgs args);
	static void TriggerRequestToolSpawn(CipherSpawnArgs args);
	static void TriggerShowAsciiTable();
};
