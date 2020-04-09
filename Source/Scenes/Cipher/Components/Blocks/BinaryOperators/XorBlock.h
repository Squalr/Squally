#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class XorBlock : public BlockBase
{
public:
	static XorBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	XorBlock(BlockType blockType);
	virtual ~XorBlock();

	void onEnter() override;
	void initializePositions() override;
	unsigned char compute() override;

private:
	typedef BlockBase super;
};
