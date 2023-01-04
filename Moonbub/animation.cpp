#include <stdio.h>
#include <time.h>
#include <SFML/Graphics.hpp>

using namespace sf;

struct Player {
	RectangleShape sprite;
	// �ִϸ��̼� ���� ����
	int fps;// �ʴ� ������ ���� (frame per sec)
	int idx;// �ִϸ��̼� �ε���
	int frames;// �ִϸ��̼� frame ��
	long ani_time;// �ִϸ��̼��� �ٲ� ���� �ð�
	long ani_delay;// ȭ�� ��ȯ�� ��

	int speed;// �ӵ�
	//������ ���õ� ����
	int is_jumping;// ���� ����
	int jumping_time;// ������ �����ϴ� �ð�
	int jump_speed;// ���� �ӵ�
};

int main(void)
{
	RenderWindow window(VideoMode(1200, 800), "Animation");
	window.setFramerateLimit(60);

	long start_time;
	long spent_time;// ���� ���� �ð�

	const int GRAVITY = 5;// �߷�
	const int PLATFORM_Y = 600;// �� �ٴ��� y��ǥ

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
	player.jump_speed = GRAVITY * 2;// ������ �ӵ��� �ö󰡰ų� ������

	start_time = clock();
	player.ani_time = start_time;
	player.jumping_time = start_time;
	player.is_jumping = 0;

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
					if (player.is_jumping == 0)
					{
						player.jumping_time = spent_time;
					}
					player.is_jumping = 1;// true
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

		//�ʿ��ϴٸ� 1000�� ���߿� ���� ó���Ұ�
		if (spent_time - player.jumping_time > 1000)
		{
			player.is_jumping = 0;
		}

		player.sprite.move(0, GRAVITY);// �߷� ����
		
		if (player.is_jumping == 1)
		{
			player.sprite.move(0, -player.jump_speed);
		}

		// �÷��̾ ���ٴڿ� ���� �ϸ�
		if (player.sprite.getPosition().y + player.sprite.getSize().y > PLATFORM_Y)// �� �ٴ��� y��ǥ�� �÷��̾��� y��ǥ�� ���� �÷��̾ ���� ������
		{
			// �� �̻� ������ �� ���� �Ѵ�
			player.sprite.setPosition(player.sprite.getPosition().x, PLATFORM_Y - player.sprite.getSize().y);
		}

		window.clear(Color::Magenta);

		window.draw(player.sprite);

		window.display();
	}

	return 0;
}