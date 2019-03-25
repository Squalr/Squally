#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class SplitterBlock : public BlockBase
{
public:
	static SplitterBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	unsigned char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	SplitterBlock(BlockType blockType);
	~SplitterBlock();

	void onEnter() override;
	void initializePositions() override;
};
