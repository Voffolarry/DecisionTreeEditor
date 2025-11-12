#include "DemoBall.h"

namespace nkentseu{
    DemoBall::DemoBall(const ApplicationProperties& props) : Application (props){};

    void DemoBall::Setup(){
        // Scale(640, 360);
        
        Background(graphics::Color(255, 255, 255, 255));

        // location = new PVector(100, 100);
        // velocity = new PVector(2.5, 5);
        
        xspeed = 3;
        yspeed = 5.5;
        
    }
    void DemoBall::Draw(){
        Background(graphics::Color::White);
        Stroke(0);
        Fill(graphics::Color(25, 50, 0, 250));
        Circle({x,y}, r );

        bool sauteX = false, sauteY = false;
        
        if((x + xspeed >= GetWindowWidth() - r ) || (x + xspeed < r))
        {
            if (x + xspeed >= GetWindowWidth() - r ) x = GetWindowWidth() - r;
            else x = r;
            sauteX = true;
            xspeed = xspeed * -1;
        }
        if ((y + yspeed >= GetWindowHeight() - r) || (y + yspeed < r) )
        {
            if (y + yspeed >= GetWindowHeight() - r ) y = GetWindowHeight() - r;
            else y = r;
            sauteY = true;
            yspeed = yspeed * -1;
        }

        if (!sauteX) x = x + xspeed;
        if (!sauteY) y = y + yspeed;
        
    }
    void DemoBall::Update(float deltaTime){

    }
}


 // location.add(velocity);
        // if ((location.x > GetWindowWidth()) || (location.x < 0)) {
        //     velocity.x = velocity.x *-1;
        // }
        // if ((location.y > GetWindowHeight()) || (location.y < 0)) {
        //     velocity.y = velocity.y *-1;
        // }
// float height = GetWindowHeight() / 2.0f;
        // x = x + velocity;
        // y = y + velocity;

        // // location.add(velocity);

        

        // // Garder dans les limites de l'écran 
        // location.x = std::max(0.0f, std::min(location.x, (float)GetWindowWidth())); 
        // location.y = std::max(0.0f, std::min(location.y, (float)GetWindowHeight())); 
    