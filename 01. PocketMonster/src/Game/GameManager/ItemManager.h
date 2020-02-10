﻿#pragma once
#include "Game/GameObject/Items/Item.h"

class ItemManager
{
public:
	bool init();

public:
	// pokemonBall Item creat
	void addPokemonBallItem(std::string _itemKey,/* char* _imageName,*/ int _x, int _y, int _imageW, int _imageH,
		std::string _itemName, int _count, int _price, std::string _descript, int _random);
	
	// potionItem creat
	void addPotionItem(std::string _itemKey, const char* _imageName, int _x , int _y ,int _imageW, int _imageH, 
		std::string _itemName, int _count , int _price, std::string _descript , int _healHp, int _hitDamage);

	void addStateHeal(std::string _itemKey,/* char* _imageName,*/ int _x, int _y, int _imageW, int _imageH,
		std::string _itemName, int _count, int _price, std::string _descript);

	void addNutrient(std::string _itemKey,/* char* _imageName,*/ int _x, int _y, int _imageW, int _imageH,
		std::string _itemName, int _count, int _price, std::string _descript , int _adddAbility);

	void addSkillMachine(std::string _itemKey, PockemonAttibute _pokemonAttibute ,/* char* _imageName,*/ int _x, int _y, int _imageW, int _imageH,
		std::string _itemName, int _count, int _price, std::string _descript, int _damage);

	std::shared_ptr<Item> findItem(std::string _itemKey);
	std::map<std::string ,std::shared_ptr<Item>> m_ItemList;
	
private:
	void itemTextInit();

private:
	itemText itemPotion;
	const int m_itemCount = 14;

private:
	DECLARE_SINGLE(ItemManager)
};
#define ITEMMANAGER ItemManager::GetInst()