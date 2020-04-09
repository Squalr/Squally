#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class BruteForceBlock : public BlockBase
{
public:
	static BruteForceBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	BruteForceBlock(BlockType blockType);
	virtual ~BruteForceBlock();

	void onEnter() override;
	void initializePositions() override;
	unsigned char compute() override;

private:
	typedef BlockBase super;
};
