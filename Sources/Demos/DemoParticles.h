#pragma once
#include "Core/Application.h"
#include "Core/Math/Vector2.h"
#include "Graphics/Color.h"
#include <vector>
#include <random>
#include <string>

namespace nkentseu {

    class DemoParticles : public Application {
        private:
            struct FireParticle {
                math::Vector2 position;
                math::Vector2 velocity;
                graphics::Color color;
                float size;
                float life;
                float maxLife;
                float growthRate;
            };

            struct FireProperties {
                    graphics::Color fireStartColor = {255, 100, 0, 255};
                    graphics::Color fireMidColor = {255, 50, 0, 200};
                    graphics::Color fireEndColor = {255, 0, 0, 100};
                    
                    int particleCount = 500;
                    float spawnRate = 0.05f;
                    float minSize = 2.0f;
                    float maxSize = 8.0f;
                    float minLife = 0.5f;
                    float maxLife = 2.0f;
                    float upwardForce = 80.0f;
                    float horizontalSpread = 20.0f;
                    float turbulence = 15.0f;
                    float growthFactor = 1.5f;
                    
                    math::Vector2 fireSource = {512, 700};
                    float sourceWidth = 100.0f;
                    
                    bool enableSmoke = true;
                    bool enableFlickering = true;
                    bool enableWind = false;
                    float windStrength = 5.0f;

                    void LoadFromArgs(const std::vector<std::string>& args);
                    void LoadFromConfigFile(const std::string& configPath);
                    
                private:
                    void ParseConfigLine(const std::string& line);
                    graphics::Color ParseColor(const std::string& colorStr);
                    std::string Trim(const std::string& str);
            };

            std::vector<FireParticle> particles;
            FireProperties fireProps;
            std::mt19937 randomGenerator;
            std::uniform_real_distribution<float> randomFloat;
            float spawnTimer = 0.0f;
            float windDirection = 1.0f;
            float windChangeTimer = 0.0f;

        public:
            DemoParticles(const ApplicationProperties& props);

        protected:
            void Setup() override;
            void Update(float deltaTime) override;
            void Draw() override;

        private:
            bool ConfigFileProvided(const std::vector<std::string>& args) const;
            void TryLoadDefaultConfig();
            void LogFireProperties();
            void UpdateWind(float deltaTime);
            void UpdateParticles(float deltaTime);
            void SpawnParticle();
            void CleanDeadParticles();
            void DrawParticle(const FireParticle& particle);
            void DrawFireBase();
            void DrawInfo();
            graphics::Color LerpColor(const graphics::Color& a, const graphics::Color& b, float t);
            float GetDeltaTime() const;
    };

} // namespace nkentseu