#include"Enemy.h"

//#include"iostream"

Enemy::Enemy(sf::Texture& texture, sf::Vector2f start_pos, int hp)
{
	m_Position = start_pos;
	m_hp = hp;
	m_speed = 250;


	m_frameHeight = 32;
	m_frameWidth = 32;
	m_numFrames = 8;
	m_currentFrame = 0;
	m_animationSpeed = 0.08f;
	m_elapsedTime = 0.f;



	m_sprite.setTexture(texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
	m_sprite.setScale(3.f, 3.f);
	m_sprite.setPosition(m_Position);
	m_size = sf::Vector2f(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height);
	
}

Enemy::~Enemy(){}

void Enemy::Update(float time)
{
	
	if (player_dead && !isDead()) {
	
		return;
	}

	if (Ataka) {

		if (m_Position.x > PlayerPosition.x) {
			timerAtaka -= time;

			m_elapsedTime += time;
			if (m_elapsedTime >= 0.1) {
				m_currentFrame = (m_currentFrame + 1) % 4;
				m_sprite.setTextureRect(sf::IntRect(
					m_currentFrame * m_frameWidth,
					2 * m_frameWidth,
					m_frameWidth,
					m_frameHeight));
				m_elapsedTime = 0.f;
			}

			if (timerAtaka <= 0.f) {
				Ataka = false; 
			}

			return;
		}
		else {
			timerAtaka -= time;

			m_elapsedTime += time;
			if (m_elapsedTime >= 0.1) {
				m_currentFrame = (m_currentFrame + 1) % 4;
				m_sprite.setTextureRect(sf::IntRect(
					m_currentFrame * m_frameWidth,
					3 * m_frameWidth,
					m_frameWidth,
					m_frameHeight));
				m_elapsedTime = 0.f;
			}

			if (timerAtaka <= 0.f) {
				Ataka = false; 
			}

			return;
		}
	}
	if (!isDead() && !Ataka) {



		sf::Vector2f dir = PlayerPosition - m_Position;
		float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
		if (len < 300.f) {
			if (len != 0.f)
				dir /= len;

			m_Position += dir * m_speed * time;
			m_sprite.setPosition(m_Position);

			//слева от игрока
			if (m_Position.x > PlayerPosition.x) {

				m_elapsedTime += time;


				if (m_elapsedTime >= m_animationSpeed) {
					m_currentFrame = (m_currentFrame + 1) % m_numFrames;
					m_sprite.setTextureRect(sf::IntRect(
						m_currentFrame * m_frameWidth,
						0,
						m_frameWidth,
						m_frameHeight));
					m_elapsedTime = 0.f;
				}

			}
			//справа от игрока
			else {
				m_elapsedTime += time;


				if (m_elapsedTime >= m_animationSpeed) {
					m_currentFrame = (m_currentFrame + 1) % m_numFrames;
					m_sprite.setTextureRect(sf::IntRect(
						m_currentFrame * m_frameWidth,
						m_frameWidth,
						m_frameWidth,
						m_frameHeight));
					m_elapsedTime = 0.f;
				}

			}
		}

	}



	//Смерть
	else {
		if (m_Position.x > PlayerPosition.x) {

			m_elapsedTime += time;


			if (m_elapsedTime >= m_animationSpeed) {
				if (m_currentFrame < 3) {
					m_currentFrame++;
					m_sprite.setTextureRect(sf::IntRect(
						m_currentFrame * m_frameWidth,
						4 * m_frameWidth,
						m_frameWidth,
						m_frameHeight));
				}
				else {
					Dead_animation = true; // анимация завершена
				}
				m_elapsedTime = 0.f;
			}
		}
		//справа от игрока
		else {
			m_elapsedTime += time;


			if (m_elapsedTime >= m_animationSpeed) {
				if (m_currentFrame < 3) {
					m_currentFrame++;
					m_sprite.setTextureRect(sf::IntRect(
						m_currentFrame * m_frameWidth,
						5 * m_frameWidth,
						m_frameWidth,
						m_frameHeight));
				}
				else {
					Dead_animation = true; // анимация завершена
				}
				m_elapsedTime = 0.f;
				
			}
			
		}
		
	}

}

void Enemy::takeDamage(int dmg)
{
	if (isDead()) return;

	m_hp -= dmg;
	//std::cout << m_hp << " ";

	if (m_hp <= 0) {
		m_currentFrame = 0;      
		m_elapsedTime = 0.f;
	}
	
}

void Enemy::ataka(float time, Player* player)
{
	if (isDead()) return;
	if (player->is_Life() == false) {
		player_dead = true;
		return;
	}
	
	sf::Vector2f dir = PlayerPosition - m_Position;
	float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len < 30.f) {
		if (len != 0.f)
			dir /= len;
	
	
			if (timerAtaka <= 0) {
				player->take_Damage(my_damage);
				timerAtaka = AtakaDelay;
				m_currentFrame = 0;
				m_elapsedTime = 0.f;

				Ataka = true;


			
		}

	}

}

void Enemy::setPlayerPosition(sf::Vector2f& player_pos)
{
	PlayerPosition = player_pos;
}

bool Enemy::isDead() const
{
	return m_hp <= 0;
}

bool Enemy::isIntersection(const sf::Sprite& bull)
{
	if (m_sprite.getGlobalBounds().intersects(bull.getGlobalBounds())) {
		//std::cout << 1;
		return true;
	}

	return false;
}
