#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "FPSComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	
	auto go = std::make_shared<dae::GameObject>();
	auto renderComponent = std::make_shared<dae::RenderComponent>();
	renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.png"));
	
	go->AddComponent(renderComponent);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	renderComponent = std::make_shared<dae::RenderComponent>();
	renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("logo.png"));
	renderComponent->SetPosition(216, 180);
	go->AddComponent(renderComponent);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = std::make_shared<dae::TextComponent>("Programming 4 Assignment", font);
	textComponent->SetPosition(80, 80);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent(textComponent);
	scene.Add(go);

	auto fpsComponent = std::make_shared<dae::FPSComponent>(font);
	fpsComponent->SetPosition(10, 10);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent(fpsComponent);
	scene.Add(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);

	
    return 0;
}