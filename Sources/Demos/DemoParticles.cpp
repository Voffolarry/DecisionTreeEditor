#include "DemoParticles.h"
#include "Core/Log.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>

namespace nkentseu {

    // FireProperties methods
    void DemoParticles::FireProperties::LoadFromArgs(const std::vector<std::string>& args) {
        for (size_t i = 0; i < args.size(); ++i) {
            if (args[i] == "--fire-color-start" && i + 1 < args.size()) {
                fireStartColor = ParseColor(args[++i]);
            }
            else if (args[i] == "--fire-color-mid" && i + 1 < args.size()) {
                fireMidColor = ParseColor(args[++i]);
            }
            else if (args[i] == "--fire-color-end" && i + 1 < args.size()) {
                fireEndColor = ParseColor(args[++i]);
            }
            else if (args[i] == "--particle-count" && i + 1 < args.size()) {
                particleCount = std::stoi(args[++i]);
            }
            else if (args[i] == "--spawn-rate" && i + 1 < args.size()) {
                spawnRate = std::stof(args[++i]);
            }
            else if (args[i] == "--min-size" && i + 1 < args.size()) {
                minSize = std::stof(args[++i]);
            }
            else if (args[i] == "--max-size" && i + 1 < args.size()) {
                maxSize = std::stof(args[++i]);
            }
            else if (args[i] == "--min-life" && i + 1 < args.size()) {
                minLife = std::stof(args[++i]);
            }
            else if (args[i] == "--max-life" && i + 1 < args.size()) {
                maxLife = std::stof(args[++i]);
            }
            else if (args[i] == "--upward-force" && i + 1 < args.size()) {
                upwardForce = std::stof(args[++i]);
            }
            else if (args[i] == "--horizontal-spread" && i + 1 < args.size()) {
                horizontalSpread = std::stof(args[++i]);
            }
            else if (args[i] == "--turbulence" && i + 1 < args.size()) {
                turbulence = std::stof(args[++i]);
            }
            else if (args[i] == "--growth-factor" && i + 1 < args.size()) {
                growthFactor = std::stof(args[++i]);
            }
            else if (args[i] == "--fire-source-x" && i + 1 < args.size()) {
                fireSource.x = std::stof(args[++i]);
            }
            else if (args[i] == "--fire-source-y" && i + 1 < args.size()) {
                fireSource.y = std::stof(args[++i]);
            }
            else if (args[i] == "--source-width" && i + 1 < args.size()) {
                sourceWidth = std::stof(args[++i]);
            }
            else if (args[i] == "--enable-smoke") {
                enableSmoke = true;
            }
            else if (args[i] == "--disable-smoke") {
                enableSmoke = false;
            }
            else if (args[i] == "--enable-flickering") {
                enableFlickering = true;
            }
            else if (args[i] == "--disable-flickering") {
                enableFlickering = false;
            }
            else if (args[i] == "--enable-wind") {
                enableWind = true;
            }
            else if (args[i] == "--disable-wind") {
                enableWind = false;
            }
            else if (args[i] == "--wind-strength" && i + 1 < args.size()) {
                windStrength = std::stof(args[++i]);
                enableWind = true;
            }
            else if (args[i] == "--fire-config" && i + 1 < args.size()) {
                LoadFromConfigFile(args[++i]);
            }
            else if (args[i] == "--fire-intensity" && i + 1 < args.size()) {
                float intensity = std::stof(args[++i]);
                upwardForce = 50.0f + intensity * 50.0f;
                turbulence = 10.0f + intensity * 10.0f;
                particleCount = static_cast<int>(500 * intensity);
            }
        }
    }

    void DemoParticles::FireProperties::LoadFromConfigFile(const std::string& configPath) {
        std::ifstream file(configPath);
        if (!file.is_open()) {
            Log.Warning("Cannot open fire config file: {0}", configPath);
            return;
        }
        
        std::string line;
        while (std::getline(file, line)) {
            ParseConfigLine(line);
        }
        file.close();
        
        Log.Info("Loaded fire configuration from: {0}", configPath);
    }

    void DemoParticles::FireProperties::ParseConfigLine(const std::string& line) {
        std::string trimmed = Trim(line);
        if (trimmed.empty() || trimmed[0] == '#') return;
        
        size_t equalsPos = trimmed.find('=');
        if (equalsPos == std::string::npos) return;
        
        std::string key = Trim(trimmed.substr(0, equalsPos));
        std::string value = Trim(trimmed.substr(equalsPos + 1));
        
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        
        try {
            if (key == "firestartcolor" || key == "startcolor") {
                fireStartColor = ParseColor(value);
            }
            else if (key == "firemidcolor" || key == "midcolor") {
                fireMidColor = ParseColor(value);
            }
            else if (key == "fireendcolor" || key == "endcolor") {
                fireEndColor = ParseColor(value);
            }
            else if (key == "particlecount") {
                particleCount = std::stoi(value);
            }
            else if (key == "spawnrate") {
                spawnRate = std::stof(value);
            }
            else if (key == "minsize") {
                minSize = std::stof(value);
            }
            else if (key == "maxsize") {
                maxSize = std::stof(value);
            }
            else if (key == "minlife") {
                minLife = std::stof(value);
            }
            else if (key == "maxlife") {
                maxLife = std::stof(value);
            }
            else if (key == "upwardforce") {
                upwardForce = std::stof(value);
            }
            else if (key == "horizontalspread") {
                horizontalSpread = std::stof(value);
            }
            else if (key == "turbulence") {
                turbulence = std::stof(value);
            }
            else if (key == "growthfactor") {
                growthFactor = std::stof(value);
            }
            else if (key == "firesourcex") {
                fireSource.x = std::stof(value);
            }
            else if (key == "firesourcey") {
                fireSource.y = std::stof(value);
            }
            else if (key == "sourcewidth") {
                sourceWidth = std::stof(value);
            }
            else if (key == "enablesmoke") {
                enableSmoke = (value == "true" || value == "1");
            }
            else if (key == "enableflickering") {
                enableFlickering = (value == "true" || value == "1");
            }
            else if (key == "enablewind") {
                enableWind = (value == "true" || value == "1");
            }
            else if (key == "windstrength") {
                windStrength = std::stof(value);
            }
        }
        catch (const std::exception& e) {
            Log.Warning("Error parsing config value '{0}': {1}", key, e.what());
        }
    }

    graphics::Color DemoParticles::FireProperties::ParseColor(const std::string& colorStr) {
        if (colorStr.size() == 7 && colorStr[0] == '#') {
            int r, g, b;
            sscanf(colorStr.c_str(), "#%02x%02x%02x", &r, &g, &b);
            return {static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b), 255};
        }
        return fireStartColor;
    }

    std::string DemoParticles::FireProperties::Trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t");
        if (start == std::string::npos) return "";
        
        size_t end = str.find_last_not_of(" \t");
        return str.substr(start, end - start + 1);
    }

    // DemoParticles methods
    DemoParticles::DemoParticles(const ApplicationProperties& props) 
        : Application(props), randomGenerator(std::random_device{}()), randomFloat(0.0f, 1.0f) {
        
        fireProps.LoadFromArgs(props.commandLineArgs);
        
        if (!ConfigFileProvided(props.commandLineArgs)) {
            TryLoadDefaultConfig();
        }
        
        particles.reserve(fireProps.particleCount * 2);
        LogFireProperties();
    }

    void DemoParticles::Setup() {
        SetWindowTitle("🔥 Fire Simulation Demo");
        SetWindowSize(1024, 768);
        Log.Info("Fire simulation started with {0} particles", fireProps.particleCount);
    }

    void DemoParticles::Update(float deltaTime) {
        UpdateWind(deltaTime);
        UpdateParticles(deltaTime);
        
        spawnTimer += deltaTime;
        while (spawnTimer >= fireProps.spawnRate && particles.size() < static_cast<size_t>(fireProps.particleCount)) {
            SpawnParticle();
            spawnTimer -= fireProps.spawnRate;
        }
        
        CleanDeadParticles();
    }

    void DemoParticles::Draw() {
        // Implementation dépendante de votre moteur graphique
        Background(graphics::Color(0, 0, 0, 255));
        
        for (const auto& particle : particles) {
            DrawParticle(particle);
        }
        
        DrawFireBase();
        DrawInfo();
    }

    bool DemoParticles::ConfigFileProvided(const std::vector<std::string>& args) const {
        for (size_t i = 0; i < args.size(); ++i) {
            if (args[i] == "--fire-config" && i + 1 < args.size()) {
                return true;
            }
        }
        return false;
    }

    void DemoParticles::TryLoadDefaultConfig() {
        const std::vector<std::string> defaultConfigs = {
            "fire.config",
            "config/fire.config",
            "assets/fire.config",
            "fire.cfg"
        };
        
        for (const auto& configPath : defaultConfigs) {
            std::ifstream testFile(configPath);
            if (testFile.is_open()) {
                testFile.close();
                fireProps.LoadFromConfigFile(configPath);
                break;
            }
        }
    }

    void DemoParticles::LogFireProperties() {
        Log.Info("Fire Properties:");
        Log.Info("  Particles: {0}", fireProps.particleCount);
        Log.Info("  Spawn Rate: {0}", fireProps.spawnRate);
        Log.Info("  Size: {0}-{1}", fireProps.minSize, fireProps.maxSize);
        Log.Info("  Life: {0}-{1}s", fireProps.minLife, fireProps.maxLife);
        Log.Info("  Source: ({0}, {1})", fireProps.fireSource.x, fireProps.fireSource.y);
        Log.Info("  Smoke: {0}", fireProps.enableSmoke ? "Enabled" : "Disabled");
        Log.Info("  Wind: {0}", fireProps.enableWind ? "Enabled" : "Disabled");
    }

    void DemoParticles::UpdateWind(float deltaTime) {
        if (fireProps.enableWind) {
            windChangeTimer += deltaTime;
            if (windChangeTimer > 2.0f) {
                windDirection = randomFloat(randomGenerator) > 0.5f ? 1.0f : -1.0f;
                windChangeTimer = 0.0f;
            }
        }
    }

    void DemoParticles::UpdateParticles(float deltaTime) {
        for (auto& particle : particles) {
            particle.velocity.y -= fireProps.upwardForce * deltaTime;
            particle.velocity.x += (randomFloat(randomGenerator) - 0.5f) * fireProps.turbulence * deltaTime;
            
            if (fireProps.enableWind) {
                particle.velocity.x += windDirection * fireProps.windStrength * deltaTime;
            }
            
            particle.position += particle.velocity * deltaTime;
            particle.size += particle.growthRate * deltaTime;
            particle.life -= deltaTime;
            
            if (fireProps.enableFlickering && randomFloat(randomGenerator) < 0.1f) {
                particle.velocity.x += (randomFloat(randomGenerator) - 0.5f) * 30.0f;
            }
        }
    }

    void DemoParticles::SpawnParticle() {
        FireParticle particle;
        
        particle.position.x = fireProps.fireSource.x + (randomFloat(randomGenerator) - 0.5f) * fireProps.sourceWidth;
        particle.position.y = fireProps.fireSource.y;
        
        particle.velocity.x = (randomFloat(randomGenerator) - 0.5f) * fireProps.horizontalSpread;
        particle.velocity.y = -randomFloat(randomGenerator) * 20.0f - 10.0f;
        
        particle.size = fireProps.minSize + randomFloat(randomGenerator) * (fireProps.maxSize - fireProps.minSize);
        particle.maxLife = fireProps.minLife + randomFloat(randomGenerator) * (fireProps.maxLife - fireProps.minLife);
        particle.life = particle.maxLife;
        particle.growthRate = particle.size * fireProps.growthFactor / particle.maxLife;
        
        particle.color = fireProps.fireStartColor;
        
        particles.push_back(particle);
    }

    void DemoParticles::CleanDeadParticles() {
        particles.erase(std::remove_if(particles.begin(), particles.end(),
            [](const FireParticle& p) { return p.life <= 0.0f; }), particles.end());
    }

    void DemoParticles::DrawParticle(const FireParticle& particle) {
        float lifeRatio = particle.life / particle.maxLife;
        graphics::Color color;
        
        if (lifeRatio > 0.66f) {
            float t = (lifeRatio - 0.66f) / 0.34f;
            color = LerpColor(fireProps.fireStartColor, fireProps.fireMidColor, t);
        }
        else if (lifeRatio > 0.33f) {
            float t = (lifeRatio - 0.33f) / 0.33f;
            color = LerpColor(fireProps.fireMidColor, fireProps.fireEndColor, t);
        }
        else {
            float t = lifeRatio / 0.33f;
            color = fireProps.fireEndColor;
            color.a = static_cast<uint8_t>(color.a * t);
        }
        
        if (fireProps.enableSmoke && lifeRatio < 0.2f) {
            color = LerpColor(color, graphics::Color(50, 50, 50, 100), 1.0f - lifeRatio * 5.0f);
        }
        
        // Utiliser les méthodes de dessin de Application
        Fill(color);
        NoStroke();
        
        // Forme variable pour plus de réalisme
        if (randomFloat(randomGenerator) > 0.7f) {
            // Rectangle allongé pour les flammes
            math::Vector2 size(particle.size * 0.7f, particle.size * 1.5f);
            Rect(particle.position - size * 0.5f, size);
        }
        else {
            // Cercle pour les braises
            Circle(particle.position, particle.size);
        }
    }

    void DemoParticles::DrawFireBase() {
        // Dessiner la base ardente
        std::vector<math::Vector2> basePoints;
        float baseWidth = fireProps.sourceWidth * 1.2f;
        float baseHeight = 30.0f;
        
        basePoints.push_back({fireProps.fireSource.x - baseWidth/2, fireProps.fireSource.y});
        basePoints.push_back({fireProps.fireSource.x - baseWidth/3, fireProps.fireSource.y - baseHeight});
        basePoints.push_back({fireProps.fireSource.x + baseWidth/3, fireProps.fireSource.y - baseHeight});
        basePoints.push_back({fireProps.fireSource.x + baseWidth/2, fireProps.fireSource.y});
        
        
        NoStroke();
        Polygon(basePoints);
    }

    void DemoParticles::DrawInfo() {
        // Afficher des informations à l'écran en haut à gauche
        Fill(graphics::Color::White);
        NoStroke();
        
        // Utiliser Println pour afficher dans la console
        // Pour l'affichage à l'écran, vous devrez implémenter du texte SDL
        Log.Debug("Particles: {0} | FPS: {1}", particles.size(), static_cast<int>(1.0f / GetDeltaTime()));
        
        // Alternative: Dessiner du texte à l'écran (si vous avez une méthode Text dans Application)
        // std::string info = "Particles: " + std::to_string(particles.size()) + 
        //                   " | FPS: " + std::to_string(static_cast<int>(1.0f / GetDeltaTime()));
        // Text(info, math::Vector2(10, 10), graphics::Color::White);
    }

    graphics::Color DemoParticles::LerpColor(const graphics::Color& a, const graphics::Color& b, float t) {
        return {
            static_cast<uint8_t>(a.r + (b.r - a.r) * t),
            static_cast<uint8_t>(a.g + (b.g - a.g) * t),
            static_cast<uint8_t>(a.b + (b.b - a.b) * t),
            static_cast<uint8_t>(a.a + (b.a - a.a) * t)
        };
    }

    float DemoParticles::GetDeltaTime() const {
        static auto lastTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;
        return std::max(deltaTime, 0.001f);
    }

} // namespace nkentseu