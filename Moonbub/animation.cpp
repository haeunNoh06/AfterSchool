#include <stdio.h>
#include <time.h>
#include <SFML/Graphics.hpp>

using namespace sf;

struct Player {
	RectangleShape sprite;
	int fps;// �ʴ� ������ ���� (frame per sec)
	int idx;// �ִϸ��̼� �ε���
	int frames;// �ִϸ��̼� frame ��
	long ani_time;// �ִϸ��̼��� �ٲ� ���� �ð�
	long ani_delay;// ȭ�� ��ȯ�� ��
	int speed;// �ӵ�

};

int main(void)
{
	RenderWindow window(VideoMode(1200, 800), "Animation");
	window.setFramerateLimit(60);

	long start_time;
	long spent_time;

	int gravity = 10;// �߷�

	Texture run[10];
	run[0].loadFromFile("./resources/imgs/Run__000.png");
	run[1].loadFromFile("./resources/imgs/Run__001.png");
	run[2].loadFromFile("./resources/imgs/Run__002.png");
	run[3].loadFromFile("./resources/imgs/Run__003.png");
	run[4].loadFromFile("./resources/imgs/Run__004.png");
	run[5].loadFromFile("./resources/imgs/Run__005.png");
	run[6].loadFromFile("./resources/imgs/Run__006.png");
	run[7].loadFromFile("./resources/imgs/Run__007.png");
	run[8].loadFromFile("./resources/imgs/Run__008.png");
	run[9].loadFromFile("./resources/imgs/Run__009.png");

	// Player
	struct Player player;
	player.fps = 10;
	player.sprite.setTexture(&run[0]);
	player.sprite.setSize(Vector2f(90, 120));
	player.sprite.setPosition(200, 200);
	player.frames = 10;
	player.ani_delay = 1000 / player.frames / 2;// 0.5�ʸ��� ����
	player.speed = 5;

	start_time = clock();
	player.ani_time = start_time;

	while (window.isOpen())
	{
		spent_time = clock() - start_time;
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Space)
				{
					// ���� ���
					player.sprite.move(0, -3);
				}
			default:
				break;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.sprite.setScale(1, 1);
			player.sprite.move(player.speed, 0);

		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			player.sprite.setScale(-1, 1);
			player.sprite.move(-player.speed, 0);
		}

		// 0.1�ʸ��� �ִϸ��̼� �׸��� �ٲ�
		while (spent_time - player.ani_time > 1000/player.ani_delay)
		{
			// �ݺ��Ϸ���
			player.ani_time = spent_time;
			player.sprite.setTexture(&run[player.idx%player.frames]);
			player.idx++;
		}

		player.sprite.move(0, gravity);// �߷� ����

		window.clear(Color::Magenta);

		window.draw(player.sprite);

		window.display();
	}

	return 0;
}