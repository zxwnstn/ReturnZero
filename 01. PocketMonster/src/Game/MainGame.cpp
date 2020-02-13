﻿#include "stdafx.h"
#include "MainGame.h"
#include "Common/GameManagers.h"
#include "GameScene/TownScene.h"
#include "GameScene/BattleScene.h"
#include "GameScene/InvenScene.h"
#include "GameObject/Items/Inventory.h"

MainGame::MainGame()
{ 
	
}

MainGame::~MainGame()
{
	
}

HRESULT MainGame::init()
{
	GameNode::init();
	IMAGEMANAGER->addImage("trainersMan", "Images/Trainers/trainers_man.bmp", 64 * 3, 64 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pailiFront", "Images/pocketmons/pailiFront.bmp", 60 * 3, 61 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pailiBack", "Images/pocketmons/pailiBack.bmp", 61 * 3, 61 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pikachuFront", "Images/pocketmons/PikachuFront.bmp", 61 * 3, 61 * 3, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("GrassTile1", "images/GrassTile1.bmp", TILE_WIDTH, TILE_HEIGHT, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bush1", "images/Bush1.bmp", TILE_WIDTH, TILE_HEIGHT, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Tree1", "images/Tree1.bmp", TILE_WIDTH, TILE_HEIGHT + 23, true, RGB(255, 0, 255));

	//rsc
	IMAGEMANAGER->addImage("인벤토리씬", "Images/InvenScene.bmp", 0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("아이템창", "Images/itemBag.bmp", 62 * 5, 64 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("임폴트창", "Images/importBag.bmp", 62 * 5, 64 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("포케볼창", "Images/ballBag.bmp", 62 * 5, 64 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아이템창태그", "Images/ItemsTag.bmp", 67 * 5, 34 * 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("임폴트창태그", "Images/KeyItemsTag.bmp", 67 * 5, 34 * 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("포케볼창태그", "Images/BallTag.bmp", 67 * 5, 34 * 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("이전화면표시", "Images/BefoeImage.bmp", 18 * 5, 17 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("다음화면표시", "Images/NextImage.bmp", 18 * 5, 17 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("현재아이템표시", "Images/itemPointer.bmp", 28 * 4, 28 * 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아이템인벤메뉴", "Images/menu.bmp", 63 * 5, 63 * 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("그외인벤메뉴", "Images/menu.bmp", 63 * 5, 63 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤메뉴상세", "Images/invenMenuBottom.bmp", 182 *3, 29* 7, true, RGB(255, 0, 255));
	
	MAPMANGER->init();
	ITEMMANAGER->init();
	POCKETMONMANAGER->init();


	//add Scene
	IMAGEMANAGER->addImage("bg", "Images/temp.bmp", 0, 0, WINSIZEX, WINSIZEY);
	SOUNDMANAGER->addStream("bgs", "Sounds/NewBarkTown.mp3", true);
	IMAGEMANAGER->addImage("현재아이템표시", "Images/itemPointer.bmp", 28 * 5, 28 * 5, true, RGB(255, 0, 255));
	std::shared_ptr<Inventory> inven = std::make_shared<Inventory>();
	inven->init();
	SCENEMANAGER->addScene("town", new TownScene);
	SCENEMANAGER->addScene("battle", new BattleScene);


	SCENEMANAGER->addScene("inven", new InvenScene(inven));
	SCENEMANAGER->scenePush("town");
	SCENEMANAGER->changeScene("town");
	sceneInit = true;

	return S_OK;
}

void MainGame::release()
{
	GameNode::release();
	MAPMANGER->release();
	POCKETMONMANAGER->release();
	ITEMMANAGER->release();
	BATTLEMANAGER->release();

	MAPMANGER->Destroy();
	POCKETMONMANAGER->Destroy();
	ITEMMANAGER->Destroy();
	BATTLEMANAGER->Destroy();
}  

void MainGame::update()
{
	if (KEYMANAGER->isOnceKeyDown(GAME_RECTMODE))
		m_showRect = !m_showRect;
	if (KEYMANAGER->isOnceKeyDown(GAME_SHOWFPS))
		m_showFPS = !m_showFPS;

	TIMEMANAGER->update(60.f);
	deltaTime = TIMEMANAGER->getElapsedTime();
	EFFECTMANAGER->update();
	SCENEMANAGER->update(deltaTime);	ANIMANAGER->update(deltaTime);
}

void MainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	SCENEMANAGER->render(getMemDC());
	SCENEMANAGER->afterRender(getMemDC());
	EFFECTMANAGER->render(getMemDC());
	if(m_showRect)
		SCENEMANAGER->debugRender(getMemDC());
	if (m_showFPS)
		TIMEMANAGER->render(getMemDC());

	getBackBuffer()->render(getHDC(), 0, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	if (sceneInit)
		return SCENEMANAGER->getCurScene()->SceneProc(hWnd, iMessage, wParam, lParam);
	else {
		switch (iMessage)
		{
		case WM_MOUSEMOVE:
			m_ptMouse.x = LOWORD(lParam);
			m_ptMouse.y = HIWORD(lParam);
			break;
		case WM_DESTROY:
			m_bLoop = false;
			PostQuitMessage(0);
			break;
		}
	}	
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
