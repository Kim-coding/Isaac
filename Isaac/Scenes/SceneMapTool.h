#pragma once
#include "Scene.h"
#include "TextGo.h"
#include "MapInfo.h"

class SpriteGo;

class SceneMapTool : public Scene
{
public:
	enum mapObjnames
	{
		rock,
		web,
		poop,
	};
	enum monsterNames
	{
		attackFly,
		boomfly,
		charger,
		dip,
		dinga,
	};
protected:
	SpriteGo* backGround;

	SpriteGo* buttonFloor;
	SpriteGo* buttonRoom;
	
	SpriteGo* buttonSave;
	SpriteGo* buttonObjDelete;
	SpriteGo* buttonMonsterDelete;


	SpriteGo* buttonRock;
	SpriteGo* buttonWep;
	SpriteGo* buttonPoop;

	SpriteGo* buttonAFly;
	SpriteGo* buttonBFly;
	SpriteGo* buttonCharger;
	SpriteGo* buttonDip;
	SpriteGo* buttonDinga;

	TextGo FloorButtonText;
	TextGo RoomButtonText;
	TextGo SaveButtonText;
	TextGo DeleteButtonText;
	
	TextGo RockButtonText;
	TextGo WebButtonText;
	TextGo PoopButtonText;

	TextGo AFlyButtonText;
	TextGo BFlyButtonText;
	TextGo ChargerButtonText;
	TextGo DipButtonText;
	TextGo DingaButtonText;

	MapInfo mapInfo;

	sf::Texture imageFloor;
	sf::Texture imageRoom;
	sf::Sprite spriteFloor;
	sf::Sprite spriteRoom;

	SpriteGo* selectedObject = nullptr;
	bool isDragging = false;

	std::vector<SpriteGo*> mapObjects;
	std::vector<SpriteGo*> monsterList;
public:
	SceneMapTool(SceneIds id);
	~SceneMapTool() override;

	void Init();
	void Release();

	std::wstring SelectFloor();
	std::wstring SelectRoom();

	void Enter();
	void Exit();

	void Update(float dt);

	void LateUpdate(float dt);
	void FixedUpdate(float dt);
	void Draw(sf::RenderWindow& window);

	void SaveMapCSV();
	void DeleteObj();
	void DeleteMonster();
	std::string ToRelativePath(const std::string& originalPath, const std::string& basePath);

};

