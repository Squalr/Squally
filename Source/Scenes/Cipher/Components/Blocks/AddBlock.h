#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class AddBlock : public BlockBase
{
public:
	static AddBlock* create(bool isToolBoxItem = false);

protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	AddBlock(bool isToolBoxItem);
	~AddBlock();

	void onEnter() override;
	void initializePositions() override;
};
