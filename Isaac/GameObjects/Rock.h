#pragma once
#include "SpriteGo.h"
#include "PlayerIsaac.h"

class SceneDev1;

class Rock : public SpriteGo
{
protected:
	PlayerIsaac* player = nullptr;
	SceneDev1* sceneDev1 = nullptr;
	bool isAlive = true;

public:
	Rock(const std::string& name);
	~Rock() override;

	void Init();
	void Release();
	void Reset();
	void Update(float dt);

	void OnBurst();          //ÆøÅº Ãæµ¹ ½Ã »èÁ¦
};

