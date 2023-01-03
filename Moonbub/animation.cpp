#include <stdio.h>
#include <SFML/Graphics.hpp>

using namespace sf;

struct Player {
	RectangleShape sprite;
	int fps;// �ʴ� ������ ���� (frame per sec)
	int idx;// �ִϸ��̼� �ε���
};

int main(void)
{
	RenderWindow window(VideoMode(1200, 800), "Animation");
	window.setFramerateLimit(60);

	Texture run[10];
	run[0].loadFromFile("./resources/images/Run__000.png");
	run[1].loadFromFile("./resources/images/Run__001.png");
	run[2].loadFromFile("./resources/images/Run__002.png");
	run[3].loadFromFile("./resources/images/Run__003.png");
	run[4].loadFromFile("./resources/images/Run__004.png");
	run[5].loadFromFile("./resources/images/Run__005.png");
	run[6].loadFromFile("./resources/images/Run__006.png");
	run[7].loadFromFile("./resources/images/Run__007.png");
	run[8].loadFromFile("./resources/images/Run__008.png");
	run[9].loadFromFile("./resources/images/Run__009.png");

	// Player
	struct Player player;
	player.fps = 10;
	player.sprite.setTexture(&run[0]);
	player.sprite.setSize(Vector2f(90, 120));
	player.sprite.setPosition(200, 200);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}


		window.clear(Color::Magenta);

		window.draw(player.sprite);

		window.display();
	}

	return 0;
}