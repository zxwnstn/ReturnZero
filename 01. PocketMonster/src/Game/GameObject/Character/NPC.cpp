﻿#include "stdafx.h"
#include "NPC.h"
#include "Common/SystemManagers.h"

NPC::NPC()
{
}

NPC::NPC(int _bPosX, int _bPosY, std::string _name, NPCEventType _anotherEventType, bool _ADHD)
{
	m_Img[DirectionUp] = IMAGEMANAGER->findImage(_name + "Back");
	m_Img[DirectionDown] = IMAGEMANAGER->findImage(_name + "Front");
	m_Img[DirectionLeft] = IMAGEMANAGER->findImage(_name + "Left");
	m_Img[DirectionRight] = IMAGEMANAGER->findImage(_name + "Right");
	m_Dialog = IMAGEMANAGER->findImage("상점NPC대화상자");
	m_DialCopleteArrow = IMAGEMANAGER->findImage("DialCopleteArrow");

	m_Name = _name;
	isADHD = _ADHD;
	m_blockPositionX = _bPosX;
	m_blockPositionY = _bPosY;
	m_DefaultDirection = DirectionDown;
	if(m_Name == "Mother")
		m_DefaultDirection = DirectionLeft;
	m_PrintDirection = m_DefaultDirection;

	m_absRect.left = _bPosX * TILE_WIDTH;
	m_absRect.right = _bPosX * TILE_WIDTH + TILE_WIDTH;
	m_absRect.top = _bPosY * TILE_HEIGHT;
	m_absRect.bottom = _bPosY * TILE_HEIGHT + TILE_HEIGHT;
	m_DialCompleteArrowRect = UTIL::IRectMakeCenter(WINSIZEX / 2, WINSIZEY - 55, 14, 9);

	anoterEventType = _anotherEventType;
	hasAnotherEvent = true;
	if (anoterEventType == NPCEventType::NPCNone)
		hasAnotherEvent = false;

}

bool NPC::init()
{
	return true;
}

void NPC::updateSenario(float _deltaTime)
{
	pastTime += _deltaTime;
	if (completedFirstOut == false) {
		if (KEYMANAGER->isOnceKeyDown(P1_X)) {
			firstOutStr = m_curSenario[senarioIndex].first;
			completedFirstOut = true;
		}
		else if (pastTime > addCharacterDelay) {
			pastTime = 0.f;
			firstOutStr += m_curSenario[senarioIndex].first[firstStrIndex++];
			if (firstOutStr.size() == m_curSenario[senarioIndex].first.size()) {
				completedFirstOut = true;
			}
		}
	}
	else if(!completedSecondOut){
		if (KEYMANAGER->isOnceKeyDown(P1_X)) {
			secondOutStr = m_curSenario[senarioIndex].second;
			completedSecondOut = true;
		}
		else if (pastTime > addCharacterDelay) {
			pastTime = 0.f;
			secondOutStr += m_curSenario[senarioIndex].second[secondStrIndex++];
			if (secondOutStr.size() >= m_curSenario[senarioIndex].second.size()) {
				completedSecondOut = true;
			}
		}
	}
	if (completedSecondOut) {
		if (KEYMANAGER->isStayKeyDown(P1_Z) || KEYMANAGER->isOnceKeyDown(P1_X)) {
			resetSenarioIndexData();
			senarioIndex++;
			if (senarioIndex == m_curSenario.size()) {
				onSenarioPrint = false;
				if (!hasAnotherEvent) {
					m_PrintDirection = m_DefaultDirection;
					isActivate = false;
				}
			}
		}
	}
}
void NPC::updatePocketCenterEvent(float _deltaTime)
{
	isActivate = false;
}
void NPC::updateShopEvent(float _deltaTime)
{
	SCENEMANAGER->scenePush("friendlyShop");
}

void NPC::resetSenarioIndexData()
{
	pastTime = 0.f;

	firstOutStr = L"";
	secondOutStr = L"";

	completedFirstOut = false;
	completedSecondOut = false;

	firstStrIndex = 0;
	secondStrIndex = 0;
}

void NPC::updateDialArrowPosition()
{
	movedArrowDist += arrowDirection;
	m_DialCompleteArrowRect.move(0, arrowDirection);
	if (std::abs(movedArrowDist) == dialArrowDistLimit) {
		movedArrowDist = 0;
		arrowDirection = -arrowDirection;
	}
}

void NPC::update(float _deltaTime)
{
	CAMERAMANAGER->rectInCamera(m_outRect, m_absRect, isCanprint);
	if (!isActivate && isADHD) {
		if (UTIL::GetRndInt(100) <= 2)
			m_PrintDirection = (Direction)UTIL::GetRndInt(4);
	}
	else {
		if (onSenarioPrint){
			updateSenario(_deltaTime);
			if (completedSecondOut)
				updateDialArrowPosition();
		}
		if (hasAnotherEvent && !onSenarioPrint) {
			if (anoterEventType == NPCEventType::NPCShop)
				updateShopEvent(_deltaTime);
			if (anoterEventType == NPCEventType::NPCPocketCenter)
				updatePocketCenterEvent(_deltaTime);
		}
	}
}

void NPC::render(HDC hdc)
{
	if (isCanprint)
	{
		m_Img[m_PrintDirection]->render(hdc, (m_outRect.left - 10), (m_outRect.top - 20) + 40, 0, 40, 80, 40);
	}
}

void NPC::afterRender(HDC hdc)
{
	if (isCanprint)
	{
		m_Img[m_PrintDirection]->render(hdc, (m_outRect.left - 10), (m_outRect.top - 20), 0, 0, 80, 40);
	}
	if (onSenarioPrint)
	{
		m_Dialog->render(hdc, 20, WINSIZEY - 185);
		UTIL::PrintText(hdc, firstOutStr.c_str(), "소야바른9", 100, WINSIZEY - 160, 65, RGB(0, 0, 0), true);
		UTIL::PrintText(hdc, secondOutStr.c_str(), "소야바른9", 100, WINSIZEY - 90, 65, RGB(0, 0, 0), true);
		if (completedSecondOut)
			m_DialCopleteArrow->render(hdc, m_DialCompleteArrowRect.left, m_DialCompleteArrowRect.top);
	}
}

void NPC::debugRender(HDC hdc)
{
	if (isCanprint)
	{
		UTIL::DrawColorRect(hdc, m_outRect, RGB(123, 41, 78), true);
	}
}

void NPC::addSenario(std::string _scriptKey, Senario _senario)
{
	m_Scripts.insert({ _scriptKey, _senario });
}

void NPC::activateNPC(Direction _dir)
{
	isActivate = true;
	switch (_dir)
	{
	case DirectionDown:
		m_PrintDirection = DirectionUp;
		break;
	case DirectionUp:
		m_PrintDirection = DirectionDown;
		break;
	case DirectionLeft:
		m_PrintDirection = DirectionRight;
		break;
	case DirectionRight:
		m_PrintDirection = DirectionLeft;
		break;
	}
	m_curSenario = (m_Scripts.find("default"))->second;
	
	senarioIndex = 0;
	onSenarioPrint = true;
}