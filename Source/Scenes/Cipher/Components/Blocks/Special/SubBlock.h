#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class SubBlock : public BlockBase
{
public:
	static SubBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	unsigned char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	SubBlock(BlockType blockType);
	~SubBlock();

	void onEnter() override;
	void initializePositions() override;
};
