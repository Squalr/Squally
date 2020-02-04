#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class InvBlock : public BlockBase
{
public:
	static InvBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	InvBlock(BlockType blockType);
	virtual ~InvBlock();

	void onEnter() override;
	void initializePositions() override;
	unsigned char compute() override;

private:
	typedef BlockBase super;
};
