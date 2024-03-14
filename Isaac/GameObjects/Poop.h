#pragma once
#include "SpriteGo.h"
#include "PlayerIsaac.h"

class SceneDev1;

class Poop : public SpriteGo
{
protected:
	PlayerIsaac* player = nullptr;
	SceneDev1* sceneDev1 = nullptr;
	bool isAlive = true;

	int count = 1;
public:
	Poop(const std::string& name);
	~Poop() override;

	void Init();
	void Release();
	void Reset();
	void Update(float dt);
	void AddCount() { ++count; }
};

