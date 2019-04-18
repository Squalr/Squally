#pragma once
#include <functional>
#include <string>

#include "cocos/math/CCGeometry.h"

class BlockBase;
class BoltBase;
class CipherPuzzleData;
class Connection;
class InputBolt;
class ImmediateBlock;
class OutputBolt;

class CipherEvents
{
public:
	static const std::string EventLoadCipher;
	static const std::string EventOpenCipher;
	static const std::string EventExitCipher;
	static const std::string EventRequestBlockSpawn;
	static const std::string EventRequestConnectionCreate;
	static const std::string EventConnectionUpdated;
	static const std::string EventConnectionDestroy;
	static const std::string EventChangeActiveCipher;
	static const std::string EventChangeDisplayDataType;
	static const std::string EventOpenImmediateEditor;
	static const std::string EventOpenAsciiTable;
	static const std::string EventTryUnlockCurrentCipher;

	struct CipherOpenArgs
	{
		std::string cipherJson;
		bool isHardMode;

		CipherOpenArgs(std::string cipherJson, bool isHardMode) : cipherJson(cipherJson), isHardMode(isHardMode)
		{
		}
	};

	struct CipherLoadArgs
	{
		CipherPuzzleData* cipherPuzzleData;

		CipherLoadArgs(CipherPuzzleData* cipherPuzzleData) : cipherPuzzleData(cipherPuzzleData)
		{
		}
	};

	struct CipherBlockSpawnArgs
	{
		std::function<BlockBase*()> spawnBlockFunc;
		cocos2d::Vec2 spawnCoords;

		CipherBlockSpawnArgs(std::function<BlockBase*()> spawnBlockFunc, cocos2d::Vec2 spawnCoords) : spawnBlockFunc(spawnBlockFunc), spawnCoords(spawnCoords)
		{
		}
	};

	struct CipherConnectionCreateArgs
	{
		BoltBase* sourceBolt;
		Connection* connection;
		cocos2d::Vec2 destination;
		bool handled;

		CipherConnectionCreateArgs(BoltBase* sourceBolt, Connection* connection, cocos2d::Vec2 destination) : sourceBolt(sourceBolt), connection(connection), destination(destination), handled(false)
		{
		}
	};

	struct CipherConnectionUpdatedArgs
	{
		Connection* connection;

		CipherConnectionUpdatedArgs(Connection* connection) : connection(connection)
		{
		}
	};

	struct CipherConnectionDestroyArgs
	{
		InputBolt* inputBolt;

		CipherConnectionDestroyArgs(InputBolt* inputBolt) : inputBolt(inputBolt)
		{
		}
	};

	struct CipherChangeActiveCipherArgs
	{
		std::string input;
		std::string output;
		bool autoScroll;

		CipherChangeActiveCipherArgs(std::string input, std::string output) : input(input), output(output), autoScroll(false)
		{
		}
		CipherChangeActiveCipherArgs(std::string input, std::string output, bool autoScroll) : input(input), output(output), autoScroll(autoScroll)
		{
		}
	};

	enum class DisplayDataType
	{
		Ascii,
		Bin,
		Dec,
		Hex
	};

	struct CipherChangeDisplayDataTypeArgs
	{
		DisplayDataType displayDataType;

		CipherChangeDisplayDataTypeArgs(DisplayDataType displayDataType) : displayDataType(displayDataType)
		{
		}
	};

	struct CipherOpenAsciiTableArgs
	{
		ImmediateBlock* immediateBlock;

		CipherOpenAsciiTableArgs(ImmediateBlock* immediateBlock) : immediateBlock(immediateBlock)
		{
		}
	};

	struct UnlockArgs
	{
		int cipherIndex;
		bool success;
		std::function<void()> callback;

		UnlockArgs(int cipherIndex, bool success, std::function<void()> callback) : cipherIndex(cipherIndex), success(success), callback(callback)
		{
		}
	};

	struct CipherExitArgs
	{
		bool victory;

		CipherExitArgs(bool victory) : victory(victory)
		{
		}
	};

	static void TriggerLoadCipher(CipherOpenArgs args);
	static void TriggerOpenCipher(CipherLoadArgs args);
	static void TriggerExitCipher(CipherExitArgs args);
	static void TriggerRequestBlockSpawn(CipherBlockSpawnArgs args);
	static void TriggerRequestConnectionCreate(CipherConnectionCreateArgs args);
	static void TriggerConnectionUpdated(CipherConnectionUpdatedArgs args);
	static void TriggerDestroyConnectionToInput(CipherConnectionDestroyArgs args);
	static void TriggerChangeActiveCipher(CipherChangeActiveCipherArgs args);
	static void TriggerChangeDisplayDataType(CipherChangeDisplayDataTypeArgs args);
	static void TriggerOpenAsciiTable(CipherOpenAsciiTableArgs args);
	static void TriggerTryUnlockCurrentCipher(UnlockArgs args);
};
