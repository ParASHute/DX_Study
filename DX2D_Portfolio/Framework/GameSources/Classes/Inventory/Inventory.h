#pragma once

#include "../Item/Item.h"
#include "../Item/SpecialItem.h"

class Inventory : public SingletonBase<Inventory> {
public:
	friend SingletonBase<Inventory>;
private:
	Inventory();
	~Inventory();

	void SetCounter(int index, int count);
	void SetUsable(int index, int count);
	void SetRooby(int rooby);

private:
	// ·çºñ(== 0), È°, ÆøÅº
	int counter[3];

	// °Ë(== 0), È°, ÆøÅº
	bool usable[3];
};