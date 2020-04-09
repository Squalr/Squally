#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class AddBlock : public BlockBase
{
public:
	static AddBlock* create(BlockType blockType = BlockType::Normal);

protected:
	AddBlock(BlockType blockType);
	virtual ~AddBlock();

	void onEnter() override;
	void initializePositions() override;
	unsigned char compute() override;

private:
	typedef BlockBase super;
};
