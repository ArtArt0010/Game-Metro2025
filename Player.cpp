#include "Player.h"
#include "PlayerController.h"
Player::Player(sf::Texture& texture, sf::Vector2f start_pos, float hp)
{
	
	m_Position = start_pos;
	m_hp = hp;
	m_controller = PlayerController::getPlayerController();
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

Player::~Player(){}

void Player::Update(float time){
	
	
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


void Player::setState(State state) {
	m_state = state;
}
