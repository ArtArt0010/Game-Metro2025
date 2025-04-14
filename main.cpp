#include <SFML/Graphics.hpp>
#include<iostream>
int main()
{
    
    sf::RectangleShape A({ 70, 90 });
    
    A.setPosition(400, 400);


    sf::RenderWindow window(sf::VideoMode(900, 800), "SFML works!");
    

    sf::Texture texture;

    if (!texture.loadFromFile("Texturs/Run_sheet.png")) // Путь относительно exe-файла
    {
        // Если не получилось, выводим ошибку в консоль
        std::cerr << "Error: Could not load texture!" << std::endl;
        return 1;
    }
    
    // Параметры анимации
    const int frameWidth = 32;
    const int frameHeight = 32;
    const int numFrames = 9;
    int currentFrame = 0;
    float animationSpeed = 0.05f;
    float elapsedTime = 0.f;

    // Настройка спрайта
    sf::Sprite sprite(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    sprite.setPosition(300, 400);
    sprite.setScale(4.f, 4.f); // Увеличим спрайт для лучшей видимости

    // Параметры движения
    float speed = 0.05f;
    bool isMoving = false;
    bool facingRight = true;

    sf::Clock clock;
    

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        elapsedTime += deltaTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Обработка управления
        isMoving = false;
        sf::Vector2f movement(0.f, 0.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            movement.x -= speed;
            isMoving = true;
            facingRight = false;
            sprite.move(-speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movement.x += speed;
            isMoving = true;
            facingRight = true;
            sprite.move(speed,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            movement.y -= speed;
            isMoving = true;
            sprite.move(0, -speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            movement.y += speed;
            isMoving = true;
            sprite.move(0, speed);
        }

        // Применяем движение
       // sprite.move(movement * deltaTime);

        // Анимация только при движении вправо/влево
        if ((movement.x != 0) && elapsedTime >= animationSpeed)
        {
            currentFrame = (currentFrame + 1) % numFrames;
            sprite.setTextureRect(sf::IntRect(
                currentFrame * frameWidth,
                0,
                facingRight ? frameWidth : -frameWidth, // Отражение спрайта
                frameHeight));
            elapsedTime = 0.f;
        }

        // Ограничение границ
        sf::Vector2f pos = sprite.getPosition();
        sf::FloatRect bounds = sprite.getGlobalBounds();

        if (pos.x < 0) sprite.setPosition(0, pos.y);
        if (pos.y < 0) sprite.setPosition(pos.x, 0);
        if (pos.x > window.getSize().x - bounds.width)
            sprite.setPosition(window.getSize().x - bounds.width, pos.y);
        if (pos.y > window.getSize().y - bounds.height)
            sprite.setPosition(pos.x, window.getSize().y - bounds.height);



        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}