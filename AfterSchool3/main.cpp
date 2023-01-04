#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>//SoundBuffer ���
//#include <SFML/Audio/SoundSource.hpp>

using namespace sf;

struct Player {
	RectangleShape sprite;
	int x;
	int y;

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

// ��ֹ�
struct Obstacle {
	RectangleShape sprite;
	int speed;
};

struct Textures {
	Texture run[10];
	Texture jump[10];
	Texture bg;
	Texture obstacle;// ��ֹ�
};

const int OBSTACLE_NUM = 3;// ��ֹ� ��
const int GRAVITY = 5;// �߷�
const int PLATFORM_Y = 600;// �� �ٴ��� y��ǥ
const int W_WIDTH = 1200, W_HEIGHT = 800;// â�� ũ��


int main(void)
{
	RenderWindow window(VideoMode(1200, 800), "Animation");
	window.setFramerateLimit(60);

	srand(time(0));

	long start_time;
	long spent_time;// ���� ���� �ð�


	struct Textures t;
	t.bg.loadFromFile("./resources/imgs/background.png");
	t.obstacle.loadFromFile("./resources/imgs/obstacle.png");
	t.run[0].loadFromFile("./resources/imgs/Run__000.png");
	t.run[1].loadFromFile("./resources/imgs/Run__001.png");
	t.run[2].loadFromFile("./resources/imgs/Run__002.png");
	t.run[3].loadFromFile("./resources/imgs/Run__003.png");
	t.run[4].loadFromFile("./resources/imgs/Run__004.png");
	t.run[5].loadFromFile("./resources/imgs/Run__005.png");
	t.run[6].loadFromFile("./resources/imgs/Run__006.png");
	t.run[7].loadFromFile("./resources/imgs/Run__007.png");
	t.run[8].loadFromFile("./resources/imgs/Run__008.png");
	t.run[9].loadFromFile("./resources/imgs/Run__009.png");
	t.jump[0].loadFromFile("./resources/imgs/Jump__000.png");
	t.jump[1].loadFromFile("./resources/imgs/Jump__001.png");
	t.jump[2].loadFromFile("./resources/imgs/Jump__002.png");
	t.jump[3].loadFromFile("./resources/imgs/Jump__003.png");
	t.jump[4].loadFromFile("./resources/imgs/Jump__004.png");
	t.jump[5].loadFromFile("./resources/imgs/Jump__005.png");
	t.jump[6].loadFromFile("./resources/imgs/Jump__006.png");
	t.jump[7].loadFromFile("./resources/imgs/Jump__007.png");
	t.jump[8].loadFromFile("./resources/imgs/Jump__008.png");
	t.jump[9].loadFromFile("./resources/imgs/Jump__009.png");

	// Player
	struct Player player;
	player.fps = 10;
	player.sprite.setTexture(&t.run[0]);
	player.sprite.setSize(Vector2f(90, 120));
	player.sprite.setPosition(200, 200);
	player.x = player.sprite.getPosition().x;// �÷��̾� x��ǥ
	player.y = player.sprite.getPosition().y;// �÷��̾� y��ǥ
	player.frames = 10;
	player.ani_delay = 1000 / player.frames / 2;// 0.5�ʸ��� ����
	player.speed = 5;
	player.jump_speed = GRAVITY * 3;// ������ �ӵ��� �ö󰡰ų� ������

	// ��ֹ�
	struct Obstacle ob[OBSTACLE_NUM];
	for (int i = 0; i < OBSTACLE_NUM; i++)
	{
		ob[i].sprite.setTexture(&t.obstacle);
		ob[i].sprite.setPosition(W_WIDTH, W_HEIGHT);
		ob[i].speed = -(rand()%5+1);
	}

	//���
	Sprite bg_sprite;
	bg_sprite.setTexture(t.bg);
	bg_sprite.setPosition(0, 0);

	// text ��Ʈ
	Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\Candara.ttf");//C����̺꿡 �ִ� ��Ʈ ��������

	// �ؽ�Ʈ
	Text text;
	char info[40];
	text.setFont(font);//��Ʈ ����
	text.setCharacterSize(24);//��Ʈ ũ��
	text.setFillColor(Color(0, 0, 0));//RGB�� ��� ǥ��
	text.setPosition(10, 10);//�ؽ�Ʈ ��ġ 0,0

	start_time = clock();
	player.ani_time = start_time;
	player.jumping_time = start_time;
	player.is_jumping = 0;

	while (window.isOpen())
	{
		spent_time = clock() - start_time;

		player.x = player.sprite.getPosition().x;// �÷��̾� x��ǥ
		player.y = player.sprite.getPosition().y;// �÷��̾� y��ǥ

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

		// ���� �ð��� ������ ����
		sprintf(info, "time: %d\n",spent_time / 1000);

		text.setString(info);

		// 0.1�ʸ��� �ִϸ��̼� �׸��� �ٲ�
		while (spent_time - player.ani_time > 1000 / player.ani_delay)
		{
			// �ݺ��Ϸ���
			player.ani_time = spent_time;
			player.sprite.setTexture(&t.run[player.idx % player.frames]);
			player.idx++;
		}

		//�ʿ��ϴٸ� 1000�� ���߿� ���� ó���Ұ�
		if (spent_time - player.jumping_time > 500)
		{
			player.is_jumping = 0;
		}

		player.sprite.move(0, GRAVITY*2);// �߷� ����

		if (player.is_jumping == 1)
		{
			player.idx = 0;
			// 0.1�ʸ��� �ִϸ��̼� �׸��� �ٲ�
			while (spent_time - player.ani_time > 1000 / player.ani_delay)
			{
				// �ݺ��Ϸ���
				player.ani_time = spent_time;
				player.sprite.setTexture(&t.jump[player.idx % player.frames]);
				player.idx++;
			}
			player.sprite.move(0, -player.jump_speed);
		}

		// �÷��̾ ���ٴڿ� ���� �ϸ�
		if (player.sprite.getPosition().y + player.sprite.getSize().y > PLATFORM_Y)// �� �ٴ��� y��ǥ�� �÷��̾��� y��ǥ�� ���� �÷��̾ ���� ������
		{
			// �� �̻� ������ �� ���� �Ѵ�
			player.sprite.setPosition(player.sprite.getPosition().x, PLATFORM_Y - player.sprite.getSize().y);
		}

		window.clear(Color::Blue);

		window.draw(bg_sprite);

		window.draw(player.sprite);

		window.draw(text);

		window.display();
	}

	return 0;
}