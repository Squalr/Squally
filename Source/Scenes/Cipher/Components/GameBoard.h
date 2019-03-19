#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class LayerColor;
}

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
	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;

	std::vector<BlockBase*> inputBlocks;
	std::vector<BlockBase*> outputBlocks;
	std::vector<BlockBase*> userBlocks;
	cocos2d::Node* inputContent;
	cocos2d::Node* outputContent;
	cocos2d::Node* userContent;
	
	cocos2d::LayerColor* gameAreaDebug;

	CipherPuzzleData* cipherPuzzleData;
	std::string currentInput;
	std::string currentOutput;
};
