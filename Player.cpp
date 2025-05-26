#include "Player.h"
#include "PlayerController.h"
#include "Weapon.h"
Player::Player(sf::Texture& texture, sf::Vector2f start_pos, int hp)
{
	
	m_Position = start_pos;
	m_hp = hp;
	m_controller = PlayerController::getPlayerController();
	m_sprite.setTexture(texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
	m_sprite.setScale(3.5, 3.5);
	m_size = sf::Vector2f(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height);

	m_frameHeight = 32;
	m_frameWidth = 32;
	m_numFrames = 8;
	m_currentFrame = 0;
	m_animationSpeed = 0.08f;
	m_elapsedTime = 0.f;

	
	
}

Player::~Player(){}

void Player::Update(float time){
	
	
	
	
	if (is_Life()) {
		m_state = State::IDLE;
		m_controller->controllPlayer(this, time);
		bool facingRight = (getDirection() == Direction::RIGHT);

		if (m_state == State::RUN) {
			if (facingRight == true) {
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
		else {
			if (facingRight == true) {
				m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
			}
			else {
				m_sprite.setTextureRect(sf::IntRect(0, m_frameWidth, m_frameWidth, m_frameHeight));
			}
		}
		m_sprite.setPosition(m_Position);
	}




	///////////////////////смерть
	else {
		m_elapsedTime += time;

		if (m_elapsedTime >= m_animationSpeed && !is_Dead) {
			if (m_currentFrame < 3) {
				m_currentFrame++;
				m_sprite.setTextureRect(sf::IntRect(
					m_currentFrame * m_frameWidth,
					5 * m_frameWidth,
					m_frameWidth,
					m_frameHeight));
			}
			else {
				is_Dead = true;
				
				m_sprite.setTextureRect(sf::IntRect(
					2 * m_frameWidth,
					5 * m_frameWidth,
					m_frameWidth,
					m_frameHeight));
			}
			m_elapsedTime = 0.f;
		}

		
		m_sprite.setPosition(m_Position);
		return;
	}

}




void Player::setState(State state) {
	m_state = state;
}

void Player::restrictions()
{
	sf::Vector2f player_pos_buff = getPosition();

	if (player_pos_buff.x < 20) {
		player_pos_buff.x = 20;
	}
	//ограничение по длине, но пока что нет длины:)
	if (player_pos_buff.x + getSize().x > mapWidth) {
		player_pos_buff.x = mapWidth - getSize().x;
	}

	if (player_pos_buff.y < 20) {
		player_pos_buff.y = 20;
	}

	if (player_pos_buff.y + getSize().y > mapHeight) {
		player_pos_buff.y = mapHeight - getSize().y; 
	}

	// применяем результат один раз
	setPosition(player_pos_buff);
}
void Player::setCountCartrige(int c_cartrige)
{
	count_cartrige += c_cartrige;
}

int Player::getCountCartrige()
{
	return count_cartrige;
}

bool Player::is_Life()
{
	if (getHP() <= 0) {
		return false;
	}
	return true;
}

void Player::setLife(bool Life)
{
	if (Life == true) {
		m_hp = 100;
		is_Dead = false;
		count_cartrige = 1;
	}
}



