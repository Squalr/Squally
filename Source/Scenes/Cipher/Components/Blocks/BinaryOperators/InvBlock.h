#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class InvBlock : public BlockBase
{
public:
	static InvBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	unsigned char compute() override;

private:
	typedef BlockBase super;
	InvBlock(BlockType blockType);
	~InvBlock();

	void onEnter() override;
	void initializePositions() override;
};
