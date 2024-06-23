import <SFML/Graphics.hpp>;
import <filesystem>;
import <fstream>;
import <iostream>;
import <vector>;
import <memory>;
import <ranges>;

import ObjectModule;
import PlayerModule;
import EnemyModule;
import MenuModule;
import MapModule;

export module GameLogicModule;

export class GameLogic
{
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Event event;
	sf::Time deltaTimeCounter;

	std::vector<std::unique_ptr<Object>> allObjects;

	Menu menu;

	int points;
	float deltaTime;

	float timeBetweenEnemies;
	float minTimeBetweenEnemies;
public:
	const float getDeltaTime();
	std::vector<std::unique_ptr<Object>>& getAllObjects();

	bool isRunning();
	void start();
	void pollEvent();

	void update();
	void draw();
	void saveScore(const int& points);
	void reset();

	GameLogic();

	bool playerAlive;
};
const float GameLogic::getDeltaTime()
{
	return deltaTime;
}

std::vector<std::unique_ptr<Object>>& GameLogic::getAllObjects()
{
	return allObjects;
}

bool GameLogic::isRunning()
{
	return window.isOpen();
}

void GameLogic::start()
{
	menu.runMenu();
	allObjects.push_back(std::make_unique<GameMap>());
	allObjects.push_back(std::make_unique<Player>(menu.isDifficultyHard()));
	playerAlive = true;

}

void GameLogic::update()
{
	deltaTime = deltaTimeCounter.asMilliseconds();
	deltaTimeCounter = clock.restart();
	timeBetweenEnemies += deltaTime;
	
	if (timeBetweenEnemies > minTimeBetweenEnemies)
	{
		allObjects.push_back(std::make_unique<Enemy>(sf::Vector2f(1920, 729)));
		timeBetweenEnemies = 0;
	}
	pollEvent();


	if (playerAlive)
	{
		//std::cout << allObjects.size() << std::endl;
		for (size_t i = 0; i < allObjects.size(); i++)
		{
			allObjects.at(i)->update(deltaTime, allObjects, points, playerAlive);
		}

	}
	else
	{
		menu.runEndMenu(points);
		saveScore(points);
		reset();
		start();
	}
}
void GameLogic::saveScore(const int& points)
{
	std::vector<int> leaderboard;
	std::string filepath = "Assets/GameData/leaderboardData.txt";

	if (std::filesystem::exists(filepath)) {
		std::ifstream file(filepath);
		std::string line;
		while (std::getline(file, line)) {
			try {
				int score = std::stoi(line);
				leaderboard.push_back(score);
			}
			catch (const std::invalid_argument& e) {
				std::cerr << "Invalid data in file: " << e.what() << std::endl;
			}
			catch (const std::out_of_range& e) {
				std::cerr << "Out of range data in file: " << e.what() << std::endl;
			}
		}
		file.close();
	}

	leaderboard.push_back(points);

	std::ranges::sort(leaderboard, std::greater<int>());


	std::ofstream outFile(filepath);
	for (const int& score : leaderboard) {
		outFile << score << "\n";
	}
	outFile.close();

}

void GameLogic::pollEvent()
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void GameLogic::draw()
{
	window.clear(sf::Color::Blue);

	for (auto& obj : allObjects)
	{
		obj->draw(window);
	}

	window.display();
}

void GameLogic::reset()
{
	allObjects.clear();
	points = 0;
}

GameLogic::GameLogic() : window(sf::VideoMode(1920, 1080), "Projekt PK4"),
						menu(1920.0f, 1080.0f, &window), points(0)
{
	timeBetweenEnemies = 0.0f;
	minTimeBetweenEnemies = 5000.0f;
	playerAlive = 0;
	clock.restart();
	deltaTime = 0; 
}