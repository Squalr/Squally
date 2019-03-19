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
	void loadCipherAtIndex(int index);

protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	GameBoard();
	~GameBoard();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	std::vector<BlockBase*> inputBlocks;
	std::vector<BlockBase*> outputBlocks;
	std::vector<BlockBase*> userBlocks;
	cocos2d::Node* inputContent;
	cocos2d::Node* outputContent;
	cocos2d::Node* userContent;

	CipherPuzzleData* cipherPuzzleData;
	std::string currentInput;
	std::string currentOutput;
};
