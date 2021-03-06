﻿#pragma once
#include "Game/GameTypes.h"

class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual bool init() = 0;
	virtual void update(float _deltaTime) = 0;

public:
	virtual void render(HDC hdc) = 0;
	virtual void afterRender(HDC hdc) = 0;
	virtual void debugRender(HDC hdc) = 0;
};
