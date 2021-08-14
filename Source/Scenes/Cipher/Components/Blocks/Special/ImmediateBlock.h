#pragma once

#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class SmartAsciiLabel;

class ImmediateBlock : public BlockBase
{
public:
	static ImmediateBlock* create(unsigned char immediate = 0, BlockType blockType = BlockType::Normal);

	void setValue(unsigned char value);
	unsigned char getValue();
	
protected:
	ImmediateBlock(BlockType blockType);
	virtual ~ImmediateBlock();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	unsigned char compute() override;

private:
	typedef BlockBase super;
	
	void loadDisplayValue();

	unsigned char charValue = 0;
	CipherEvents::DisplayDataType displayDataType = CipherEvents::DisplayDataType::Ascii;

	cocos2d::Sprite* spriteAscii = nullptr;
	cocos2d::Sprite* spriteBin = nullptr;
	cocos2d::Sprite* spriteDec = nullptr;
	cocos2d::Sprite* spriteHex = nullptr;
	cocos2d::Sprite* spriteAsciiSelected = nullptr;
	cocos2d::Sprite* spriteBinSelected = nullptr;
	cocos2d::Sprite* spriteDecSelected = nullptr;
	cocos2d::Sprite* spriteHexSelected = nullptr;
	SmartAsciiLabel* displayLabel = nullptr;
};
