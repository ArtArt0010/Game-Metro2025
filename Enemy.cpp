#include"Enemy.h"
//#include"EnemyManager.h"


Enemy::Enemy(sf::Texture& texture, sf::Vector2f start_pos, int hp)
{
	m_Position = start_pos;
	m_hp = hp;
	m_speed = 100;

	m_sprite.setTexture(texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
	m_sprite.setScale(4.f, 4.f);
	m_size = sf::Vector2f(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height);

	m_frameHeight = 32;
	m_frameWidth = 32;
	m_numFrames = 8;
	m_currentFrame = 0;
	m_animationSpeed = 0.08f;
	m_elapsedTime = 0.f;

	
}

Enemy::~Enemy(){}

void Enemy::Update(float time)
{
	sf::Vector2f dir = PlayerPosition - m_Position;
	float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len != 0.f)
		dir /= len;

	m_Position += dir * m_speed * time;
	m_sprite.setPosition(m_Position);

	m_sprite.move(dir * m_speed * time);
}

void Enemy::takeDamage(int dmg)
{
	m_hp -= dmg;
}

void Enemy::ataka(int dmg)
{
}

void Enemy::setPlayerPosition(sf::Vector2f& player_pos)
{
	PlayerPosition = player_pos;
}

bool Enemy::isDead() const
{
	return m_hp <= 0;
}
