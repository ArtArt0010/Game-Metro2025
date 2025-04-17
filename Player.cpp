#include "Player.h"
#include "PlayerController.h"
Player::Player(sf::Texture& texture, sf::Vector2f start_pos, float hp)
{
	m_Position = start_pos;
	m_hp = hp;
	m_controller = PlayerController::getPlayerController();
	m_sprite.setTexture(texture);
	m_size = sf::Vector2f(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height);
}

Player::~Player(){}

void Player::Update(float time){
	m_state = State::IDLE;
	m_controller->controllPlayer(this, time);
	if (m_state == State::RUN) {

	}
	else {

	}
	m_sprite.setPosition(m_Position);

}
void Player::setState(State state) {
	m_state = state;
}
