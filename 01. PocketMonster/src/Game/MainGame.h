﻿#pragma once
#include "Common/GameNode.h"
#include "GameScene/InvenScene.h"

class MainGame 
	: public GameNode
{
private:

public:
	MainGame();
	~MainGame();

	HRESULT init() override;	
	void release() override;
	void update() override;
	void render() override;

	bool sceneInit = false;

public:
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

private:
	void myloadImage(std::string defaultName, std::string path, int _size);
	float deltaTime;
};

