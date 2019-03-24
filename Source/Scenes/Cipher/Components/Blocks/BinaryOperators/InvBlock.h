#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class InvBlock : public BlockBase
{
public:
	static InvBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	InvBlock(BlockType blockType);
	~InvBlock();

	void onEnter() override;
	void initializePositions() override;
};
