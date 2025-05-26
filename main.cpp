#include <SFML/Graphics.hpp>
#include<iostream>
#include"Load_Texture.h"
#include "Player.h"
#include "Automate.h"
#include "Bullet.h"
#include<vector>
#include "Enemy.h"
#include "Spavn.h"
#include "Cartrige.h"
#include "View.h"
#include "LevelLoad.h"
#include <string>
#include<ctime>
using namespace std;

int main()
{
    sf::Font font;
    font.loadFromFile("Texturs/RodchenkoBTT.ttf");
    srand(time(0));
    sf::Text text("", font, 50);
    sf::Text text2("", font, 30);




    float timerDead = 5.0;



    sf::RenderWindow window(sf::VideoMode(1240, 900), "SFML works!");

    view.reset(sf::FloatRect(0, 0, 1240, 900));

    textures::Level_texture();
    std::vector<sf::Sprite> levelTiles;

    int num_level = 1;
    string name_fail_map = "Levels/level_" + to_string(num_level);
    LevelLoad(name_fail_map + ".txt", textures::level_texture, levelTiles);

    textures::Player_setTextures();
    Player* player = new Player(textures::player_texture, sf::Vector2f(200, 300), 100);

    textures::Automat_texture();
    Automat* automat = new Automat(textures::automat_texture, sf::Vector2f(200, 300), 30);

    textures::Enemy_texture();
   
    vector<Enemy> enemies;
    spawnEnemy(10, 15, enemies, textures::enemy_texture);
    
    textures::Cartrige_texture();
    

    textures::Bullet_texture();

    vector<Bullet> bullets;
    float fireCooldown = 0.f;
    float fireRate = 0.2f;

    vector<Cartriges> cartrige;
    spawnCartriges(4, 6, cartrige, textures::cartrige_texture);

    sf::Clock clock;

    
    while (window.isOpen()) {
      
 
        float time = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        
        player->Update(time);
        player->restrictions();


        getCameraPosition(player->getPosition());
        automat->Update_weapon(time, player, window);
        
        for (auto& enemy : enemies) {
            sf::Vector2f player_p = player->getPosition();
            enemy.setPlayerPosition(player_p);
            enemy.ataka(time, player);
            enemy.Update(time);
        }
     
        

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

            bool hit = false;
            for (auto& enemy : enemies) {
                if (enemy.isIntersection(bullets[i].getSprite())) {
                    enemy.takeDamage(bullets[i].m_damage);
                    hit = true;
                    break;
                }
            }

            if (hit || !bullets[i].isAlife()) {
                bullets.erase(bullets.begin() + i);
            }
            else {
                ++i;
            }
        }


        if (player->getPosition().x > 3840 && player->getPosition().x < 3904 && player->getPosition().y > 340 && player->getPosition().y < 416) {
            cartrige.clear();
            bullets.clear();
            enemies.clear();
            num_level++;

            name_fail_map = "Levels/level_" + to_string(num_level);
            LevelLoad(name_fail_map + ".txt", textures::level_texture, levelTiles);

            sf::Vector2f p(100, 400);
            player->setPosition(p);

            
           
            spawnEnemy(10, 15, enemies, textures::enemy_texture);
          
        }
        
        if (player->is_Life() == false) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                cartrige.clear();
                bullets.clear();
                enemies.clear();
                LevelLoad("Levels/level_1.txt", textures::level_texture, levelTiles);
                sf::Vector2f p(100, 400);
                player->setPosition(p);
                player->setLife(1);


                spawnEnemy(10, 15, enemies, textures::enemy_texture);
            }
       }
        
        window.setView(view);
        window.clear();

        
       
        for (auto& tile : levelTiles) {
            window.draw(tile);
        }

        for (auto & bullet : bullets) {
            window.draw(bullet.getSprite());
        }
        for (auto& crt : cartrige) {
            window.draw(crt.getSprite());
        }

        window.draw(player->getSprite());
        window.draw(automat->getSprite());
       // window.draw(enemy->getSprite());
        for (auto& enemy : enemies) {
            window.draw(enemy.getSprite());
        }
        if (!player->is_Life()) {
            text.setString("Game Over");
            text2.setString("Enter -> restart");

            text.setFillColor(sf::Color::Red);
            text2.setFillColor(sf::Color::Red);
            text.setCharacterSize(100);
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.width / 2, textBounds.height / 2);
            text.setPosition(view.getCenter());
            text2.setPosition(view.getCenter().x, view.getCenter().y + 80);
            window.draw(text);
            window.draw(text2);
        }

        window.display();
    }
    
    delete player;
    delete automat;

    return 0;
}