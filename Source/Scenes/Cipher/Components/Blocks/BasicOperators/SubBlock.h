#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class SubBlock : public BlockBase
{
public:
	static SubBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	SubBlock(BlockType blockType);
	virtual ~SubBlock();

	void onEnter() override;
	void initializePositions() override;
	unsigned char compute() override;

private:
	typedef BlockBase super;
};
