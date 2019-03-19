#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class BruteForceBlock : public BlockBase
{
public:
	static BruteForceBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	BruteForceBlock(BlockType blockType);
	~BruteForceBlock();

	void onEnter() override;
	void initializePositions() override;
};
