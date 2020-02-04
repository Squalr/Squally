#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class SplitterBlock : public BlockBase
{
public:
	static SplitterBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	SplitterBlock(BlockType blockType);
	virtual ~SplitterBlock();

	void onEnter() override;
	void initializePositions() override;
	unsigned char compute() override;

private:
	typedef BlockBase super;
};
