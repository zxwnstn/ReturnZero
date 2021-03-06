﻿#pragma once
#include "Game/GameObject/Items/Item.h"
class Close
	:public Item
{
public:
	Close(ItemType _type, class Image* _potionImage, UTIL::IRECT _rect, std::string _name,
		int _count, int _price, std::string _description);
	~Close();

	virtual bool init() override;
	virtual void update(float _deltaTime) override;

	virtual void render(HDC hdc) override;
	virtual void afterRender(HDC hdc) override;
	virtual void debugRender(HDC hdc) override;
};

