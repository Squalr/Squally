#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

class BlockBase;
class CipherPuzzleData;
class ClickableNode;

class GameBoard : public CipherComponentBase
{
public:
	static GameBoard* create();

	void loadPuzzleData(CipherPuzzleData* cipherPuzzleData);

protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	GameBoard();
	~GameBoard();

	void onEnter() override;
	void initializePositions() override;

	std::vector<BlockBase*> inputOutputBlocks;
};
