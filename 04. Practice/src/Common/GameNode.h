﻿#pragma once
#include "Common/SystemManagers.h"

static Image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class GameNode {

public:
	GameNode();
	~GameNode();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

public:
	Image* getBackBuffer()	{ return _backBuffer; }
	HDC getHDC()			{ return _hdc; }
	HDC getMemDC()			{ return _backBuffer->getMemDC(); }

private:
	HDC	_hdc;
	static bool _managerInit;
};