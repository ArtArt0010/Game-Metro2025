#include <SFML/Graphics.hpp>
#include<iostream>
#include"Load_Texture.h"
#include "Player.h"
#include "Automate.h"
#include "Bullet.h"
using namespace std;

int main()
{

    


    sf::RenderWindow window(sf::VideoMode(900, 800), "SFML works!");

    textures::Player_setTextures();
    Player* player = new Player(textures::player_texture, sf::Vector2f(200, 300), 100);

    textures::Automat_texture();
    Automat* automat = new Automat(textures::automat_texture, sf::Vector2f(200, 300), 500);

    textures::Bullet_texture();

    Bullet* bullet = nullptr;
    

    sf::Clock clock;


    while (window.isOpen()) {
       /* float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 300;*/
        float time = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        player->Update(time);
        automat->Update_weapon(time, player, window);

        if (automat->getState() == State_w::SHOOTING && bullet == nullptr) {
            bullet = new Bullet(textures::bullet_texture, automat->getPosition(), automat->getDirectionMausse());
            bullet->Update(time);
        }
       
        if (bullet) {
            bullet->Update(time);
            /*if (!bullet->isAlive()) {
                delete bullet;
                bullet = nullptr;
            }*/
        }


        window.clear();

        if (bullet) {
            window.draw(bullet->getSprite());
        }

        window.draw(player->getSprite());
        window.draw(automat->getSprite());
        
        window.display();
    }

    delete player;
    delete automat;
    return 0;
}