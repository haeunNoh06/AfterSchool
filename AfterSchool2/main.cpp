#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>

using namespace sf;

const int row = 4;
const int CARD_W = 300;
const int CARD_H = 200;

struct Card {
	RectangleShape sprite;
	int id;
	int type;
	int is_clicked;// ���ȴ°�
};

int main(void) {

	RenderWindow window(VideoMode(1200, 800), "AfterSchool2");// ȭ�� ũ��, ����
	window.setFramerateLimit(60);// 60�ʸ��� �� ���� ���ư���

	// f : �Ҽ�
	// Vector2i : ����
	Vector2i mouse_pos;// ���콺 ��ǥ
	int flipped_num = 0;// ���� �������� ī���� ����

	Texture t[8 + 1];
	t[0].loadFromFile("./resources/images/ch0.png");
	t[1].loadFromFile("./resources/images/ch1.png");
	t[2].loadFromFile("./resources/images/ch2.png");
	t[3].loadFromFile("./resources/images/ch3.png");
	t[4].loadFromFile("./resources/images/ch4.png");
	t[5].loadFromFile("./resources/images/ch5.png");
	t[6].loadFromFile("./resources/images/ch6.png");
	t[7].loadFromFile("./resources/images/ch7.png");
	t[8].loadFromFile("./resources/images/ch8.png");

	Font font;
	font.loadFromFile("c:/Windows/Fonts/arial.ttf");

	// �ؽ�Ʈ
	Text text;
	text.setFont(font);
	text.setCharacterSize(30);// ���� ũ��
	text.setFillColor(Color::White);
	text.setPosition(0, 0);
	char info[40];

	struct Card cards[row][row];
	int n = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < row; j++)
		{
			cards[i][j].sprite.setSize(Vector2f(CARD_W, CARD_H));
			cards[i][j].sprite.setPosition(j * CARD_W, i * CARD_H);// j�� Ŀ������ x���� 100����, i�� Ŀ������ y���� 200����
			cards[i][j].sprite.setTexture(&t[0]);// ������ �׸��� 0�̱� ������ 1����
			cards[i][j].type = 1 + n / 2;
			cards[i][j].id = n + 1;
			cards[i][j].is_clicked = 0;
			n++;
		}
	}

	while (window.isOpen())
	{
		mouse_pos = Mouse::getPosition(window);// ���콺 ��ǥ �ǽð����� �ޱ�

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			// �� �� ������ �� ���� ����
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left)
				{
					flipped_num++;// �ʿ���� �ڵ�
					for (int i = 0; i < row; i++)
					{
						for (int j = 0; j < row; j++)
						{
							// ���콺�� ���̹Ƿ� �浹�� �ƴ� ���԰��踦 ��Ÿ���� ��
							if (cards[i][j].sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
							{
								cards[i][j].is_clicked = 1;// true
							}
						}
					}
				}
			}
		}
		
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < row; j++)
			{
				// Ŭ���ϸ� ī�� ������
				if (cards[i][j].is_clicked)
				{
					// �׸��� �ִ� ��������Ʈ�� ����
					cards[i][j].sprite.setTexture(&t[cards[i][j].type]);
				}
			}
		}

		sprintf(info, "(%d, %d) clicks %d\n", mouse_pos.x, mouse_pos.y, flipped_num);
		text.setString(info);
		
		window.clear(Color::Black);

		window.draw(text);
		
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < row; j++)
			{
				window.draw(cards[i][j].sprite);
			}
		}

		window.display();
		
	}
	return 0;
}