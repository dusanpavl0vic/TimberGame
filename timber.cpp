#include <SFML/Graphics.hpp>


using namespace sf;

int main()
{
    sf::VideoMode vm = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(vm, "Timber!", sf::Style::None);

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
    
    Clock clock;


    Texture treeTexture;
    if(!treeTexture.loadFromFile("./assets/graphics/tree.png")){
        std::printf("Error loading tree texture");
    }
    sf::Sprite treeSprite(treeTexture);

    float treeX = static_cast<float>(vm.width/2) - treeTexture.getSize().x/2;
    float treeY = 0.f;
    treeSprite.setPosition(sf::Vector2f(treeX, treeY));

    Texture beeTexture;
    if(!beeTexture.loadFromFile("./assets/graphics/bee.png")){
        std::printf("Error loading bee texture");
    }
    sf::Sprite beeSprite(beeTexture);
    beeSprite.setPosition(sf::Vector2f(0, 800));

    bool beeActive = false;
    float beeSpeed = 0.5f;

    Texture cloudTexture;
    if(!cloudTexture.loadFromFile("./assets/graphics/cloud.png")){
        std::printf("Error loading cloud texture");
    }
    sf::Sprite cloudSprite1(cloudTexture);
    sf::Sprite cloudSprite2(cloudTexture);
    sf::Sprite cloudSprite3(cloudTexture);

    cloudSprite1.setPosition(sf::Vector2f(0.f, 0.f));
    cloudSprite2.setPosition(sf::Vector2f(0.f, 250.f));
    cloudSprite3.setPosition(sf::Vector2f(0.f, 500.f));

    bool cloudActive1 = false;
    bool cloudActive2 = false;
    bool cloudActive3 = false;

    float cloudSpeed1 = 0.0f;
    float cloudSpeed2 = 0.0f;
    float cloudSpeed3 = 0.0f;

    std::printf("Before the loop\n");


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