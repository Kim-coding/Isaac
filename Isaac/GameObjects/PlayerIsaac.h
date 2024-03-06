#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class PlayerIsaac : public SpriteGo
{
public:
	struct ClipInfo
	{
		std::string idle;
		std::string move;
		bool filpX = false;
		sf::Vector2f point;

		ClipInfo()
		{
		}
		ClipInfo(const std::string& idle, const std::string& move, bool flipX, const sf::Vector2f& point)
			: idle(idle), move(move), filpX(flipX), point(point)
		{
		}
	};

protected:
	Animator animator;


	sf::Vector2f direction;
	float speed = 400.f;

	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;
	
	int maxHp = 1000;
	int hp;
	bool isAlive = true;
	bool isNoDamage = false;
	float noDamageTime = 0.5f;
	float noDamageTimer = 0.f;

	static std::string IdleDown;
	static std::string IdleSide;
	static std::string IdleUp;
	static std::string MoveDown;
	static std::string MoveSide;
	static std::string MoveUp;

public:
	PlayerIsaac(const std::string& name = "");
	~PlayerIsaac() override;

	void TestInstance();
	void TestStaic();

	void Init() override;
	void Reset() override;
	void Update(float dt) override;

	void Cry();           //발사체 : 눈물 공격

	void OnDamage(int damage);
	void OnDie();

};

