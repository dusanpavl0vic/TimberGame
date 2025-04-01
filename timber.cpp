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

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

void updateBranches(int seed){
    for(int j = NUM_BRANCHES - 1; j > 0; j--){
        branchPositions[j] = branchPositions[j - 1];
    }
    srand((int)time(0) + seed);
    int r = rand() % 5;
    switch (r)
    {
        case 0:
            branchPositions[0] = side::LEFT;
            break;
        case 1:
            branchPositions[0] = side::RIGHT;
            break;
        default:
            branchPositions[0] = side::NONE;
            break;
    }
}
int main()
{
    sf::VideoMode vm = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(vm, "Timber!", sf::Style::None);
    window.setFramerateLimit(1000);

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
    backgroundSprite.setScale(scaleX, scaleY);
    

    std::printf("Windows size: %u %u\n", vm.width, vm.height);
    
    


    Texture treeTexture;
    if(!treeTexture.loadFromFile("./assets/graphics/tree.png")){
        std::printf("Error loading tree texture");
    }
    sf::Sprite treeSprite(treeTexture);

    float treeX = static_cast<float>(vm.width/2) - (treeTexture.getSize().x * scaleX)/2;
    float treeY = 0.f;
    treeSprite.setScale(scaleX, scaleY);
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



    Clock clock;

    RectangleShape timeBar;
    float timeBarWidth = 400.f;
    float timeBarHeight = 80.f;
    timeBar.setSize(sf::Vector2f(timeBarWidth, timeBarHeight));
    timeBar.setFillColor(sf::Color::Red);
    timeBar.setScale(scaleX, scaleY);
    timeBar.setPosition(sf::Vector2f(vm.width/2 - timeBarWidth * scaleX / 2, vm.height - timeBarHeight * scaleY));

    Time getTimeTotal;
    float timeRemaining = 6.f;
    float timeBarWidthPerSecond = timeBarWidth / timeRemaining;

    bool gamePaused = true;
    
    int score = 0;

    sf::Text messageText;
    sf::Text scoreText;

    Font font;
    if(!font.loadFromFile("./assets/fonts/KOMIKAP_.ttf")){
        std::printf("Error loading font");
    }
    messageText.setFont(font);
    scoreText.setFont(font);

    messageText.setString("Press Enter to start");
    scoreText.setString("Score: 0");

    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    messageText.setScale(scaleX, scaleY);
    scoreText.setScale(scaleX, scaleY);

    messageText.setFillColor(sf::Color::White);
    scoreText.setFillColor(sf::Color::White);

    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    messageText.setPosition(sf::Vector2f(vm.width/2.0f, vm.height/2.0f));
    scoreText.setPosition(sf::Vector2f(20.f, 20.f));

    Texture branchTexture;
    if(!branchTexture.loadFromFile("./assets/graphics/branch.png")){
        std::printf("Error loading branch texture");
    }

    for (int i = 0; i < NUM_BRANCHES; i++){
        branches[i].setTexture(branchTexture);
        branches[i].setScale(scaleX, scaleY);
        branches[i].setPosition(-2000, -2000);
        branches[i].setOrigin(220.f, 20.f);
    }


   
    updateBranches(1);
    updateBranches(2);
    updateBranches(3);
    updateBranches(4);
    updateBranches(5);
    updateBranches(6);
    updateBranches(7);
    updateBranches(8);


    Texture playerTexture;
    if(!playerTexture.loadFromFile("./assets/graphics/player.png")){
        std::printf("Error loading player texture");
    }
    sf::Sprite playerSprite(playerTexture);
    playerSprite.setScale(scaleX, scaleY);
    playerSprite.setPosition(sf::Vector2f(580.f * scaleX, 720.f * scaleY));
    
    side playerSide = side::LEFT;

    Texture axeTexture;
    if(!axeTexture.loadFromFile("./assets/graphics/axe.png")){
        std::printf("Error loading axe texture");
    }
    sf::Sprite axeSprite(axeTexture);
    axeSprite.setScale(scaleX, scaleY);
    axeSprite.setPosition(sf::Vector2f(700.f * scaleX, 830.f * scaleY));

    Texture RIPTexture;
    if(!RIPTexture.loadFromFile("./assets/graphics/rip.png")){
        std::printf("Error loading RIP texture");
    }
    sf::Sprite RIPSprite(RIPTexture);
    RIPSprite.setScale(scaleX, scaleY);
    RIPSprite.setPosition(sf::Vector2f(600.f * scaleX, 860.f * scaleY));

    const float AXE_POSITION_LEFT = 700.f * scaleX;
    const float AXE_POSITION_RIGHT = 1075.f * scaleX;

    Texture logTexture;
    if(!logTexture.loadFromFile("./assets/graphics/log.png")){
        std::printf("Error loading log texture");
    }

    sf::Sprite logSprite(logTexture);
    logSprite.setScale(scaleX, scaleY);
    logSprite.setPosition(sf::Vector2f(810.f * scaleX, 720.f * scaleY));

    bool logActive = false;
    float logSpeedX = 1000.f;
    float logSpeedY = -1000.f;

    bool acceptInut = false;


    sf::SoundBuffer chopBuffer;
    if(!chopBuffer.loadFromFile("./assets/sound/chop.wav")){
        std::printf("Error loading chop sound");
    }
    sf::Sound chop;
    chop.setBuffer(chopBuffer);

    sf::SoundBuffer deathBuffer;
    if(!deathBuffer.loadFromFile("./assets/sound/death.wav")){
        std::printf("Error loading chop sound");
    }
    sf::Sound death;
    death.setBuffer(deathBuffer);

    sf::SoundBuffer ootBuffer;
    if(!ootBuffer.loadFromFile("./assets/sound/out_of_time.wav")){
        std::printf("Error loading chop sound");
    }
    sf::Sound oot;
    oot.setBuffer(ootBuffer);


    

    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(100);
    fpsText.setScale(scaleX, scaleY);
    fpsText.setFillColor(sf::Color::White);

    fpsText.setString("FPS: 0000");

    FloatRect fpsRect = fpsText.getLocalBounds();

    std::printf("%f %f", fpsRect.height, fpsRect.width);

    fpsText.setOrigin(fpsRect.left + fpsRect.width, fpsRect.top);
    
    fpsText.setPosition(vm.width + 20.f, 40.f);
    

    std::printf("Zvuk ucitan");
    while(window.isOpen()){
            
        Time dt = clock.restart();

        float fps = 1.0f / dt.asSeconds();
        fpsText.setString("FPS: " + std::to_string((int)fps));
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyReleased && !gamePaused){
                acceptInut = true;

                axeSprite.setPosition(3000 * scaleX, axeSprite.getPosition().y);

            }
        }


        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            gamePaused = false;

            score = 0;
            timeRemaining = 6.f;

            for (int i = 1; i < NUM_BRANCHES; i++){
                branchPositions[i] = side::NONE;
            }

            RIPSprite.setPosition(675, 2000 * scaleY);
            playerSprite.setPosition(580 * scaleX, 720 * scaleY);

            acceptInut = true;
        }

        if (acceptInut){
            if (Keyboard::isKeyPressed(Keyboard::Right)){

                playerSide = side::RIGHT;

                score++;

                timeRemaining += (2 / score ) + .15;

                axeSprite.setPosition(AXE_POSITION_RIGHT, axeSprite.getPosition().y);

                playerSprite.setPosition(1200 * scaleX, 720 * scaleY);

                updateBranches(score);

                logSprite.setPosition(810 * scaleX, 720 * scaleY);
                logSpeedX = -5000 * scaleX;
                logActive = true;

                acceptInut = false;
                chop.play();
            
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)){

                playerSide = side::LEFT;

                score++;

                timeRemaining += (2 / score ) + .15;

                axeSprite.setPosition(AXE_POSITION_LEFT, axeSprite.getPosition().y);

                playerSprite.setPosition(580 * scaleX, 720 * scaleY);

                updateBranches(score);

                logSprite.setPosition(810 * scaleX, 720 * scaleY);
                logSpeedX = 5000 * scaleX;
                logActive= true;

                acceptInut = false;
                chop.play();
            
            }

        }

        if (!gamePaused)
        {
            
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond*timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.f)
            {
                gamePaused = true;

                messageText.setString("Out of time!");

                FloatRect textRect = messageText.getLocalBounds();

                messageText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
                messageText.setPosition(sf::Vector2f(vm.width/2.0f, vm.height/2.0f));

                oot.play();
            }

            if(!beeActive){
                score += 10;
                beeActive = true;

                srand((int)time(0));
                beeSpeed = (rand() % 100) + 300; // koliko piksela po sekundi da se pomera

                srand((int)time(0) * 10);
                float beeY = (rand() % vm.height/2) + 100;
                beeSprite.setPosition(1430, beeY);
                //std::printf("Bee Y: %f\n", beeY);

                
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
                //std::printf("Cloud1 Y: %f\n", cloud1Y);
                
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
                //std::printf("Cloud1 Y: %f\n", cloud2Y);
                
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
                //std::printf("Cloud1 Y: %f\n", cloud3Y);
                
            }
            else{
                cloudSprite3.setPosition(cloudSprite3.getPosition().x + (cloudSpeed3 * dt.asSeconds()), 
                                        cloudSprite3.getPosition().y);
                

                if(cloudSprite3.getPosition().x > 1440){
                    cloudActive3 = false;
                }
            }

            std::stringstream ss;
            ss << "Score: " << score;
            scoreText.setString(ss.str());

            for(int i = 0; i < NUM_BRANCHES; i++){

                float height = i * 150 * scaleY;
                
                if(branchPositions[i] == side::LEFT){
                    branches[i].setPosition(610 * scaleX, height);
                    
                    branches[i].setRotation(180.f);
                }
                else if(branchPositions[i] == side::RIGHT){
                    branches[i].setPosition(1330 * scaleX, height);
                    branches[i].setRotation(0.f);
                }
                else{
                    branches[i].setPosition(2000, height);
                }
                
            }

            if (logActive){
                logSprite.setPosition(logSprite.getPosition().x + (logSpeedX * dt.asSeconds()), logSprite.getPosition().y + (logSpeedY * dt.asSeconds()));
    
                if(logSprite.getPosition().x < -100 || logSprite.getPosition().x > 2000 * scaleX){
                    logActive = false;
                    logSprite.setPosition(810 * scaleX, 720 * scaleY);
                }
            }

            if (branchPositions[5] == playerSide){

                gamePaused = true;
                acceptInut = false;

                if ( playerSide == side::RIGHT){
                    RIPSprite.setPosition(1255 * scaleX, 760 * scaleY);
                }
                else{
                    RIPSprite.setPosition(525 * scaleX, 760 * scaleY);
                }

                playerSprite.setPosition(2000 * scaleX, 660 * scaleY);
                axeSprite.setPosition(2000 * scaleX, 830 * scaleY);

                messageText.setString("SQUISHED!!");

                FloatRect textRect = messageText.getLocalBounds();

                messageText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);

                messageText.setPosition(vm.width / 2.f, vm.height / 2.f);

                death.play();
            }
        }


        window.clear();

        window.draw(backgroundSprite);

        window.draw(cloudSprite1);
        window.draw(cloudSprite2);
        window.draw(cloudSprite3);

        for(int i = 0; i < NUM_BRANCHES; i++){
            window.draw(branches[i]);
        }

        window.draw(treeSprite);

        window.draw(logSprite);
        window.draw(playerSprite);
        window.draw(axeSprite);
        window.draw(RIPSprite);
        
        window.draw(beeSprite);

        window.draw(timeBar);

        window.draw(scoreText);
        window.draw(fpsText);
        if (gamePaused)
        {
            window.draw(messageText);
        }


        window.display();

    }

    
    return 0;
}