#include "Automate.h"
#include "Automat_Controller.h"
//#include "Bullet.h"
//#include <SFML/Graphics.hpp>

Automat::Automat(sf::Texture& texture, sf::Vector2f start_pos, int cartridges)
{
	
	m_frameHeight_w = 16;
	m_frameWidth_w = 32;
	m_numFrames_w = 5;
	m_currentFrame_w = 0;
	m_animationSpeed_w = 0.05f;
	m_elapsedTime_w = 0.f;

	m_Position_weapon = start_pos;
	m_cartridges = cartridges;
	m_controller = AutomatController::getAutomatController();
	m_sprite_weapon.setTexture(texture);
	m_sprite_weapon.setTextureRect(sf::IntRect(0, 0, m_frameWidth_w, m_frameHeight_w));
	m_sprite_weapon.setScale(8.f, 8.f);
	m_size_weapon = sf::Vector2f(m_sprite_weapon.getTextureRect().width, m_sprite_weapon.getTextureRect().height);

	


}

Automat::~Automat(){}

void Automat::Update_weapon(float time, Player* player, sf::RenderWindow& window)
{
	m_state = State_w::STOP;
	m_controller->controllAutomat(this, player, window, time);

	
	m_elapsedTime_w += time;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getCartridges() != 0){
		m_state = State_w::SHOOTING;
		if (m_elapsedTime_w >= m_animationSpeed_w) {
			m_currentFrame_w = (m_currentFrame_w + 1) % m_numFrames_w;

			m_sprite_weapon.setTextureRect(sf::IntRect(
				m_currentFrame_w * m_frameWidth_w,
				0,                                
				m_frameWidth_w,
				m_frameHeight_w
			));
			m_elapsedTime_w = 0.f;
		}


	
	}
	else
	{
		
		m_currentFrame_w = 0;
		m_sprite_weapon.setTextureRect(sf::IntRect(0, 0, m_frameWidth_w, m_frameHeight_w));
		m_elapsedTime_w = 0.f;
	}


	//if (getCartridges() == 0) {//перезарядка, но нужно доделать!!!
	//	setCartriges(30);
	//}
}



void Automat::setState(State_w state)
{
	m_state = state;
}

State_w Automat::getState()
{
	return m_state;
}







