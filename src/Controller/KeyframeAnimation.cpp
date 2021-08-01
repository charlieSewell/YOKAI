#include "KeyframeAnimation.hpp"

KeyframeAnimation::KeyframeAnimation() 
{
    shader = std::make_unique<Shader>("content/Shaders/vertexShader.vert", "content/Shaders/fragmentShader.frag");
    shader->useShader();
    shader->setVec3("skyColor",glm::vec3(0.05,0.05,0.05));
    shader->setBool("isAnimated",false);
    shader->setVec3("lightColor",glm::vec3(1.0,1.0,1.0));
    shader->setVec3("lightPos",glm::vec3(500,200,500));
    currentFrame = 0;
    totalTime = 0;
    ticksPerSecond = 30;
    animationFinished = true;
}

void KeyframeAnimation::readFile(const std::string &textPath)
{
    std::ifstream file(textPath);
    std::string path;
    if (file) 
    {
        while (std::getline(file, path)) 
        {
            collectModel(path);
        }
    } 
    else 
    {
        std::cout << "Error opening file: " + textPath << std::endl;
    }
}

void KeyframeAnimation::collectModel(const std::string &modelPath)
{
    models.push_back(std::make_shared<Model>(loader.loadModel(modelPath)));
}

void KeyframeAnimation::setAnimation(std::string name)
{
    currentAnimation = std::move(name);
}

std::string KeyframeAnimation::getCurrentAnimation() const
{
    return currentAnimation;
}

void KeyframeAnimation::addAnimation(const std::string& animation, int firstFrame, int lastFrame)
{
    if (firstFrame < 0) 
    {
        firstFrame = 1;
    }

    if (lastFrame > models.size()) 
    {
        lastFrame = models.size() - 1;
    }

    animations.emplace(animation, std::pair<int, int>(firstFrame, lastFrame));
}

void KeyframeAnimation::setCurrentFrame(double deltaTime) 
{

    //std::cout << getCurrentFrame() << "\n";
    totalTime += deltaTime;
    if (totalTime > ((animations.at(currentAnimation).second - animations.at(currentAnimation).first + 1) / ticksPerSecond))
    {
        totalTime = 0;
    }

    swapAnimationCheck(); 
    currentFrame = static_cast<int>(totalTime * ticksPerSecond);
    currentFrame += animations.at(currentAnimation).first - 1;
}

void KeyframeAnimation::swapAnimationCheck() 
{
    if (currentAnimation != tempAnimation) 
    {
        totalTime = 0;
    }

    tempAnimation = currentAnimation;
}

int KeyframeAnimation::getCurrentFrame() const
{
    return currentFrame;
}

void KeyframeAnimation::draw(Transform t) 
{
    shader->useShader();
    shader->setVec3("viewPos", EMS::getInstance().fire(ReturnVec3Event::getPlayerPosition));

    models[currentFrame]->Draw(*shader, t.getMatrix());

}

void KeyframeAnimation::setTPS(float tps) 
{
    ticksPerSecond = tps;
}

float KeyframeAnimation::getTPS() const
{
    return ticksPerSecond;
}

void KeyframeAnimation::setAnimationFinished(bool a) 
{
    animationFinished = a;
}

void KeyframeAnimation::checkAnimationFinished() 
{
    if (currentFrame == animations.at(currentAnimation).second - 1) 
    {
        animationFinished = true;
    } 
    else 
    {
        animationFinished = false;
    }
    //std::cout << animationFinished << "\n";
}

bool KeyframeAnimation::getAnimationFinished() const
{
    return animationFinished;
}