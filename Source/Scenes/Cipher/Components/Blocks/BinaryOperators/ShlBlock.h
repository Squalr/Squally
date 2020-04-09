#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ShlBlock : public BlockBase
{
public:
	static ShlBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	ShlBlock(BlockType blockType);
	virtual ~ShlBlock();

	void onEnter() override;
	void initializePositions() override;
	unsigned char compute() override;

private:
	typedef BlockBase super;
};
