#pragma once
#include <SFML/Graphics.hpp>
#include "../Wall/Wall.h"
#include "../Bullet/Bullet.h"
#include <list>

using namespace sf;

class PickUp;

class Player
{
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;
	const float START_IMMUNE_MS = 200;

	const int START_AMMOUNITION = 120;   // 초기 총 탄환 수
	const int MAX_MAGAZINE = 30;   // 최대 장전 탄환 수
	const int MAX_Ammunitation = 120;   // 최대 보유 탄환 수

	const float RELOAD_INTERBAL = 2.f;   // 재장전 시간
	const float SHOOT_DELAY = 0.1f; // 탄환 생성 딜레이

	Vector2f position;

	std::string texFileName;
	Sprite sprite;

	Vector2i resolution;
	IntRect arena;

	int tileSize;

	Vector2f direction;
	float speed;

	int health;
	int maxHealth;
	float immuneMs;

	Time lastHit;

	const int BULLET_CACHE_SIZE = 1000;
	std::list<Bullet*> unuseBullets;
	std::list<Bullet*> useBullets;

	float distanceToMuzzle;
	
	float shootTimer;
	float reloadTime;
	bool isReload;
	int ammunition;   // 가지고 있는 총 탄환 수
	int magazine;   // 탄창 안의 탄환 수

public:
	Player();
	~Player();

	void Shoot(Vector2f dir);

	void Spawn(IntRect arena, Vector2i res, int tileSize);

	bool OnHitted(Time timeHit);

	Time GetLastTime() const;
	FloatRect GetGobalBound() const;
	Vector2f GetPosition() const;
	float GetRotation() const;
	Sprite GetSprite() const;
	int GetHealth() const;

	bool UpdateCollision(const std::vector<Zombie*>& zombies);
	bool UpdateCollision(const std::vector<PickUp*>& items);
	void Update(float dt, std::vector<Wall*> walls);
	void Draw(RenderWindow& window);
	void GetHealthItem(int amount);
	void GetAmmuItem(int amount);
	void UpgradeSpeed();
	void UpgradeMaxHealth();

	void SetIsReload(bool isReload);
	bool GetIsReload();

	int GetAmmunition() const;
	int GetMagazine() const;
};

