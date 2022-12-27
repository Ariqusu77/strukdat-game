#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <systemsatu.hpp>
#include <iostream>

int main()
{
    //initial
    int map_offsetxplus = 0;
    int map_offsetxminus = 0;
    int map_offsetyplus = 0;
    int map_offsetyminus = 0;

    int velo = 2;

    //generating
    srand(39);
    Noisesystem* World_data = new Noisesystem(rand(),rand());

    World_data->Noisesystem::Generating_noise(3);
    World_data->Noisesystem::Rendering_noise(2);

    srand(19);
    Noisesystem* Secondary_data = new Noisesystem(rand(),rand());

    Secondary_data->Noisesystem::Generating_noise(3);
    Secondary_data->Noisesystem::Rendering_noise(2);

    //window game
    sf::RenderWindow window(sf::VideoMode(1920,960), "");
    window.setFramerateLimit(60);

    sf::Texture texture0;
    if (!texture0.loadFromFile("image/environment.png")){
        return EXIT_FAILURE;
    }

    sf::Texture texture1;
    if (!texture1.loadFromFile("image/char.png")){
        return EXIT_FAILURE;
    }

    sf::Sprite grass(texture0);
    sf::IntRect block0(0,0,64,64);
    grass.setTextureRect(block0);
    grass.setScale(0.5,0.5);

    sf::Sprite tree(texture0);
    sf::IntRect block1(64,0,64,64);
    tree.setTextureRect(block1);
    tree.setScale(0.5,0.5);

    sf::Sprite water(texture0);
    sf::IntRect block2(128,0,64,64);
    water.setTextureRect(block2);
    water.setScale(0.5,0.5);

    sf::Sprite chara(texture1);
    chara.setScale(0.5,0.5);
    chara.setOrigin(16,16);
    chara.setPosition(960,480);

    //threading
    //sf::Thread Threadleft(&generateleft, &World_data, &Secondary_data);

    //start loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            //move right
            map_offsetxminus = map_offsetxminus + velo;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {   
            //move up
            map_offsetyplus = map_offsetyplus + velo;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            //move left
            map_offsetxplus = map_offsetxplus + velo;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {   
            //move down
            map_offsetyminus = map_offsetyminus + velo;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        for(auto i=0; i<96; i++){
            for(auto j=0; j<96; j++){
                if(World_data->renderred_maps_data[i][j] !=0){
                    water.setPosition(-556+ i*32 +map_offsetxplus -map_offsetxminus, -1056+ j*32 +map_offsetyplus -map_offsetyminus);
                    window.draw(water);
                }else{
                    grass.setPosition(-556+ i*32 +map_offsetxplus -map_offsetxminus, -1056+ j*32 +map_offsetyplus -map_offsetyminus);
                    window.draw(grass);
                    if(Secondary_data->renderred_maps_data[i][j] !=0){
                        tree.setPosition(-556+ i*32 +map_offsetxplus -map_offsetxminus, -1056+ j*32+map_offsetyplus -map_offsetyminus);
                        window.draw(tree);
                    }
                }
            }
        }
        window.draw(chara);

        // Update the window
        window.display();
    }
    return 0;
}