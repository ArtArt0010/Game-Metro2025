#include <SFML/Graphics.hpp>
#include<iostream>
#include"Load_Texture.h"
#include "Player.h"
#include "Automate.h"
#include "Bullet.h"
#include<vector>
#include "Enemy.h"
#include "Cartrige.h"
using namespace std;

int main()
{

    float timerDead = 5.0;


    sf::RenderWindow window(sf::VideoMode(900, 800), "SFML works!");

    textures::Player_setTextures();
    Player* player = new Player(textures::player_texture, sf::Vector2f(200, 300), 100);

    textures::Automat_texture();
    Automat* automat = new Automat(textures::automat_texture, sf::Vector2f(200, 300), 30);

    textures::Enemy_texture();
    Enemy* enemy = new Enemy(textures::enemy_texture, sf::Vector2f(500, 300), 50);
    
    textures::Cartrige_texture();
    

    textures::Bullet_texture();

    vector<Bullet> bullets;
    float fireCooldown = 0.f;
    float fireRate = 0.2f;

    vector<Cartriges> cartrige;
    cartrige.emplace_back(textures::cartrige_texture, sf::Vector2f(600, 400));
    cartrige.emplace_back(textures::cartrige_texture, sf::Vector2f(400, 200));

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
        

        enemy->ataka(time, player);
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
       
        for (int i = 0; i < cartrige.size(); ) {
            cartrige[i].CartrigeReload(player);
            if (!cartrige[i].flag_crt) {
                cartrige.erase(cartrige.begin() + i);
            }
            else {
                ++i;
            }
        }

        for (int i = 0; i < bullets.size(); ) {
            bullets[i].Update(time);

            if (enemy && enemy->isIntersection(bullets[i].getSprite())) {
                enemy->takeDamage(bullets[i].m_damage);
                bullets.erase(bullets.begin() + i);
                continue;
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
        for (auto& crt : cartrige) {
            window.draw(crt.getSprite());
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