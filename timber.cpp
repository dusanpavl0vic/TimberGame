#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>

using namespace sf;

int main()
{
    sf::VideoMode vm = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(vm, "Timber!", sf::Style::None);

    float scaleX = vm.width / 1920.0f;
    float scaleY = vm.height / 1080.0f;
    std::printf("Scale X: %f\n", scaleX);
    std::printf("Scale Y: %f\n", scaleY);

    Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("./assets/graphics/background.png")){
        std::printf("Error loading background texture");
    }

    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setPosition(sf::Vector2f(0.f, 0.f));
    backgroundSprite.setScale(
        static_cast<float>(vm.width) / backgroundTexture.getSize().x,
        static_cast<float>(vm.height) / backgroundTexture.getSize().y
    );

    std::printf("Windows size: %u %u\n", vm.width, vm.height);
    
    


    Texture treeTexture;
    if(!treeTexture.loadFromFile("./assets/graphics/tree.png")){
        std::printf("Error loading tree texture");
    }
    sf::Sprite treeSprite(treeTexture);

    float treeX = static_cast<float>(vm.width/2) - (treeTexture.getSize().x * scaleX)/2;
    float treeY = 0.f;
    treeSprite.setScale(scaleX, 1);
    treeSprite.setPosition(sf::Vector2f(treeX, treeY));

    Texture beeTexture;
    if(!beeTexture.loadFromFile("./assets/graphics/bee.png")){
        std::printf("Error loading bee texture");
    }
    sf::Sprite beeSprite(beeTexture);
    beeSprite.setScale(scaleX, scaleY);
    beeSprite.setPosition(sf::Vector2f(0, 800 * scaleY));
    

    bool beeActive = false;
    float beeSpeed = 0.5f;

    Texture cloudTexture;
    if(!cloudTexture.loadFromFile("./assets/graphics/cloud.png")){
        std::printf("Error loading cloud texture");
    }
    sf::Sprite cloudSprite1(cloudTexture);
    sf::Sprite cloudSprite2(cloudTexture);
    sf::Sprite cloudSprite3(cloudTexture);

    cloudSprite1.setPosition(sf::Vector2f(0.f, 0.f * scaleY));
    cloudSprite1.setScale(scaleX, scaleY);
    cloudSprite2.setPosition(sf::Vector2f(0.f, 250.f * scaleY));
    cloudSprite2.setScale(scaleX, scaleY);
    cloudSprite3.setPosition(sf::Vector2f(0.f, 500.f * scaleY));
    cloudSprite3.setScale(scaleX, scaleY);

    bool cloudActive1 = false;
    bool cloudActive2 = false;
    bool cloudActive3 = false;

    float cloudSpeed1 = 0.0f;
    float cloudSpeed2 = 0.0f;
    float cloudSpeed3 = 0.0f;

    std::printf("Before the loop\n");

    bool gamePaused = true;

    Clock clock;

    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            gamePaused = false;
        }


        if (!gamePaused)
        {
            
            Time dt = clock.restart();

            if(!beeActive){
                beeActive = true;

                srand((int)time(0));
                beeSpeed = (rand() % 100) + 300; // koliko piksela po sekundi da se pomera

                srand((int)time(0) * 10);
                float beeY = (rand() % vm.height/2) + 100;
                beeSprite.setPosition(1430, beeY);
                std::printf("Bee Y: %f\n", beeY);

                
            }
            else{
                beeSprite.setPosition(beeSprite.getPosition().x - (beeSpeed * dt.asSeconds()), 
                                        beeSprite.getPosition().y);

                if(beeSprite.getPosition().x < -100){
                    beeActive = false;
                }
            }

            if (!cloudActive1){
                cloudActive1 = true;

                srand((int)time(0) * 10);
                cloudSpeed1 = (rand() % 100); // koliko piksela po sekundi da se pomera

                srand((int)time(0) * 10);
                float cloud1Y = (rand() % 150);
                cloudSprite1.setPosition(-200, cloud1Y);
                std::printf("Cloud1 Y: %f\n", cloud1Y);
                
            }
            else{
                cloudSprite1.setPosition(cloudSprite1.getPosition().x + (cloudSpeed1 * dt.asSeconds()), 
                                        cloudSprite1.getPosition().y);
                

                if(cloudSprite1.getPosition().x > 1440){
                    cloudActive1 = false;
                }
            }

            if (!cloudActive2){
                cloudActive2 = true;

                srand((int)time(0) * 20);
                cloudSpeed2 = (rand() % 100); // koliko piksela po sekundi da se pomera

                srand((int)time(0) * 20);
                float cloud2Y = (rand() % 300) - 100;
                cloudSprite2.setPosition(-400, cloud2Y);
                std::printf("Cloud1 Y: %f\n", cloud2Y);
                
            }
            else{
                cloudSprite2.setPosition(cloudSprite2.getPosition().x + (cloudSpeed2 * dt.asSeconds()), 
                                        cloudSprite2.getPosition().y);
                

                if(cloudSprite2.getPosition().x > 1440){
                    cloudActive2 = false;
                }
            }

            if (!cloudActive3){
                cloudActive3 = true;

                srand((int)time(0) * 30);
                cloudSpeed3 = (rand() % 100); // koliko piksela po sekundi da se pomera

                srand((int)time(0) * 30);
                float cloud3Y = (rand() % 450) - 150;
                cloudSprite3.setPosition(-500, cloud3Y);
                std::printf("Cloud1 Y: %f\n", cloud3Y);
                
            }
            else{
                cloudSprite3.setPosition(cloudSprite3.getPosition().x + (cloudSpeed3 * dt.asSeconds()), 
                                        cloudSprite3.getPosition().y);
                

                if(cloudSprite3.getPosition().x > 1440){
                    cloudActive3 = false;
                }
            }

        }

        window.clear();

        window.draw(backgroundSprite);

        window.draw(cloudSprite1);
        window.draw(cloudSprite2);
        window.draw(cloudSprite3);

        window.draw(treeSprite);
        
        window.draw(beeSprite);

        window.display();

    }

    
    return 0;
}