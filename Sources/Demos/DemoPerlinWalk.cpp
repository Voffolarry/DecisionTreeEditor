#include "DemoPerlinWalk.h" 
 
namespace nkentseu { 
    DemoPerlinWalk::DemoPerlinWalk(const ApplicationProperties& props)  
        : Application(props), tx(0.0f), ty(10000.0f) {} 
     
    void DemoPerlinWalk::Setup() { 
        position = math::Vector2(GetWindowWidth() / 2.0f, GetWindowHeight() / 2.0f); 
        Background(graphics::Color::White); 
    } 

    void DemoPerlinWalk::Update(float deltaTime){

    }
     
    void DemoPerlinWalk::Draw() { 
        // Dessiner le marcheur 
        Fill(graphics::Color::Red); 
        NoStroke(); 
        Circle(position, 4.0f); 
         
        // Utiliser le bruit de Perlin pour la position   - la loi utilise c'est Noise
        float noiseX = math::Random::Noise(tx); 
        float noiseY = math::Random::Noise(ty); 
         
        // Mapper de [0,1] à la taille de la fenêtre 
        position.x = math::Random::Map(noiseX, 0.0f, 1.0f, 0.0f, (float)GetWindowWidth()); 
        position.y = math::Random::Map(noiseY, 0.0f, 1.0f, 0.0f, (float)GetWindowHeight()); 
         
        // Avancer dans l'"espace-temps" du bruit 
        tx += 0.9f; 
        ty += 0.6f; 
    } 
} 
 
// Fonction de création 
nkentseu::Application* CreatePerlinWalkDemo(const 
nkentseu::ApplicationProperties& props) { 
    return new nkentseu::DemoPerlinWalk(props); 
} 