#pragma once
#include "../Core/Application.h"
#include "../Core/Math/Vector2.h"
#include "../Core/Math/Random.h"


namespace nkentseu{
  class DemoBall : public Application{
      public: 
        DemoBall(const ApplicationProperties& props);
      protected:
        void Setup() override;
        void Update(float deltaTime) override;
        void Draw() override;
      public:
        float x = 200;
        float y = 200;
        float xspeed = 3;
        float yspeed = 5.5;
        float r = 50;

        // class PVector{
        //   public:
        //     float x ;
        //     float y ;
        //     PVector location;
        //     PVector velocity;

        //   PVector(float x_, float y_){
        //     x = x_;
        //     y = y_;
        //   }
        //   void add(PVector v){
        //     y = y + v.y;
        //     x = x + v.x;
        //   }
        // };
        
  }; 
}

  //   class DemoBall : public Application{
   
  //   public: 
  //     DemoBall(const ApplicationProperties& props);
      
  //   protected:
  //     void Setup() override;
  //     void Update(float deltaTime) override;
  //     void Draw() override;
  //   public:
  //     float x;
  //     float y;
  //     float location;
  //     float velocity;

  //     DemoBall(float x_, float y_){
  //       x = x_;
  //       y = y_;
  //     }
  // };
