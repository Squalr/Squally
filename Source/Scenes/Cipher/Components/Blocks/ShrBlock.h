#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ShrBlock : public BlockBase
{
public:
	static ShrBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	ShrBlock(BlockType blockType);
	~ShrBlock();

	void onEnter() override;
	void initializePositions() override;
};
