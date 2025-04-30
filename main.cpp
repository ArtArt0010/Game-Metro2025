#include <SFML/Graphics.hpp>
#include<iostream>
#include"Load_Texture.h"
#include "Player.h"
#include "Automate.h"
#include "Bullet.h"
#include<vector>
#include "Enemy.h"
using namespace std;

int main()
{

    


    sf::RenderWindow window(sf::VideoMode(900, 800), "SFML works!");

    textures::Player_setTextures();
    Player* player = new Player(textures::player_texture, sf::Vector2f(200, 300), 100);

    textures::Automat_texture();
    Automat* automat = new Automat(textures::automat_texture, sf::Vector2f(200, 300), 30);

    textures::Enemy_texture();
    Enemy* enemy = new Enemy(textures::enemy_texture, sf::Vector2f(500, 300), 10);
    

    textures::Bullet_texture();

    vector<Bullet> bullets;
    float fireCooldown = 0.f;
    float fireRate = 0.2f;

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
        sf::Vector2f p = player->getPosition();
        enemy->setPlayerPosition(p);
        enemy->Update(time);

        fireCooldown -= time;
        if (automat->getState() == State_w::SHOOTING && automat->getCartridges() != 0) {
            if (fireCooldown <= 0.f) {
                bullets.emplace_back(textures::bullet_texture, automat->getPosition(), automat->getDirectionMausse());
                fireCooldown = fireRate;
                automat->setCartriges(automat->getCartridges() - 1);
            }

        }
       
        for (int i = 0; i < bullets.size(); ) {
            bullets[i].Update(time);
            if (enemy->isIntersection(bullets[i].getSprite())) {
                enemy->takeDamage(bullets[i].m_damage);
              // bullets[i]
                
            }
            if (!bullets[i].isAlife()) {
                bullets.erase(bullets.begin() + i);

            }
            else {
                ++i;

            }
        }

        

        window.clear();

        for (auto & bullet : bullets) {
            window.draw(bullet.getSprite());
        }

        window.draw(player->getSprite());
        window.draw(automat->getSprite());
        window.draw(enemy->getSprite());

        

        window.display();
    }

    delete player;
    delete automat;
    delete enemy;
    return 0;
}