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
	unsigned char compute() override;

private:
	typedef BlockBase super;
	ImmediateBlock(BlockType blockType);
	~ImmediateBlock();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadDisplayValue();

	unsigned char charValue;
	CipherEvents::DisplayDataType displayDataType;

	cocos2d::Sprite* spriteAscii;
	cocos2d::Sprite* spriteBin;
	cocos2d::Sprite* spriteDec;
	cocos2d::Sprite* spriteHex;
	cocos2d::Sprite* spriteAsciiSelected;
	cocos2d::Sprite* spriteBinSelected;
	cocos2d::Sprite* spriteDecSelected;
	cocos2d::Sprite* spriteHexSelected;

	SmartAsciiLabel* displayLabel;
};
