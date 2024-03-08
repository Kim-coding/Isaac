#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class SceneDev1;

class PlayerIsaac : public SpriteGo
{
	std::map<sf::Keyboard::Key, sf::Vector2f> directionMap;

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
	SceneDev1* sceneDev1 = nullptr;

	static std::string IdleDown;
	static std::string IdleSide;
	static std::string IdleUp;
	static std::string MoveDown;
	static std::string MoveSide;
	static std::string MoveUp;

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

	float timer = 0.f;
	float timerInterval = 3.f;

	bool isCrying = false;
	float cryInterval = 0.5f;
	float cryTimer = 0.f;
	float tearsSpeed = 1000.f;
	int tearsDamage = 10;

	bool doorCrash = false;

public:
	PlayerIsaac(const std::string& name = "");
	~PlayerIsaac() override;

	void TestInstance();
	void TestStaic();

	void Init() override;
	void Reset() override;
	void Update(float dt) override;

	void Cry(sf::Vector2f direction);           //�߻�ü : ���� ����

	void OnDamage(int damage);
	void OnDie();

};

