#include"Enemy.h"

//#include"iostream"

Enemy::Enemy(sf::Texture& texture, sf::Vector2f start_pos, int hp, int damage, float speed, int sprite_size, float animation_speed, float scale)
{
	m_Position = start_pos;
	m_hp = hp;
	m_speed = speed;
	my_damage = damage;

	m_frameHeight = sprite_size;
	m_frameWidth = sprite_size;
	m_numFrames = 8;
	m_currentFrame = 0;
	m_animationSpeed = animation_speed;
	m_elapsedTime = 0.f;



	m_sprite.setTexture(texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
	m_sprite.setScale(scale, scale);
	m_sprite.setPosition(m_Position);
	m_size = sf::Vector2f(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height);

	skorpBuffer.loadFromFile("Sounds/enemy_run.wav");
	skorpSound.setBuffer(skorpBuffer);
	
}

Enemy::~Enemy(){}

void Enemy::Update(float time)
{
	
	if (player_dead && !isDead()) {
	
		return;
	}
	m_prevPosition = getPosition();
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


		//if ((skorpSound.getStatus() != sf::Sound::Playing) && !saund_play) {
		//	skorpSound.play();
		//	//saund_play = true;
		//}
		sf::Vector2f dir = PlayerPosition - m_Position;
		float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
		if (len < 300.f) {
			if (len != 0.f)
				dir /= len;

			m_Position += dir * m_speed * time;
			m_sprite.setPosition(m_Position);

			//����� �� ������
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
			//������ �� ������
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



	//������
	else {
		skorpSound.stop();
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
					Dead_animation = true; // �������� ���������
				}
				m_elapsedTime = 0.f;
			}
		}
		//������ �� ������
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
					Dead_animation = true; // �������� ���������
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
void Enemy::colisions(const std::vector<Train>& collidables) {
	sf::FloatRect playerBounds = m_sprite.getGlobalBounds();

	for (const auto& object : collidables) {
		if (playerBounds.intersects(object.getSprite().getGlobalBounds())) {

			setPosition(m_prevPosition);

			break;
		}
	}
}