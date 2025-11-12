#include "DemoRandomWalk.h"

     
namespace nkentseu { 
    DemoRandomWalk::DemoRandomWalk(const ApplicationProperties& props)  
        : Application(props) {} 
     
    void DemoRandomWalk::Setup() { 
        position = math::Vector2(GetWindowWidth() / 2.0f, GetWindowHeight() / 2.0f); 
        Background(graphics::Color::White); 
    } 
     
    void DemoRandomWalk::Update(float deltaTime) { 
        // La logique de mise à jour sera dans Draw pour cet exemple simple 
    } 
     
    void DemoRandomWalk::Draw() { 
        // Dessiner le marcheur 
        Fill(graphics::Color::Black); 
        NoStroke(); 
        Circle(position, 4.0f); 
         
        // Prendre un pas aléatoire 
        int choice = math::Random::Range(0, 3); 
         
        if (choice == 0) { 
            position.x++; 
        } else if (choice == 1) { 
            position.x--; 
        } else if (choice == 2) { 
            position.y++; 
        } else { 
            position.y--; 
        } 
         
        // Garder dans les limites de l'écran 
        position.x = std::max(0.0f, std::min(position.x, (float)GetWindowWidth())); 
        position.y = std::max(0.0f, std::min(position.y, (float)GetWindowHeight())); 
    } 
} 
 
// Fonction de création 
nkentseu::Application* CreateRandomWalkDemo(const nkentseu::ApplicationProperties& props) { return new nkentseu::DemoRandomWalk(props); 
}// namespace nkentseu