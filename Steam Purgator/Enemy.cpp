#include "Enemy.h"



Enemy::Enemy(Texture Texture, int hp, int maxHp, float size_x, float size_y, bool alive, float speed) : health(hp), maxHealth(maxHp), size_x(size_x), size_y(size_y), alive(alive), speed(speed)
{

}

Enemy::~Enemy()
{

}

void Enemy::attack()
{

}

void Enemy::destroyEnemy(vector<Enemy&> listEnemy, int index)
{
	if (!listEnemy.empty()) {
		for (auto it : listEnemy) {
			listEnemy.erase(listEnemy.begin() - 1 + index);
		}
	}
}

void Enemy::setHealth(int health)
{
	this->health = health;
}

int Enemy::getHealth()
{
	return health;
}




