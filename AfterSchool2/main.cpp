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
	int id_i;
	int id_j;
	int type;
	int is_clicked;// ���ȴ°�
	int is_cleared;// ������ ���� ī���ΰ�
};

void swap_card(struct Card* c1, struct Card* c2)
{
	struct Card tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

int main(void) {

	RenderWindow window(VideoMode(1200, 800), "AfterSchool2");// ȭ�� ũ��, ����
	window.setFramerateLimit(60);// 60�ʸ��� �� ���� ���ư���

	// f : �Ҽ�
	// Vector2i : ����
	Vector2i mouse_pos;// ���콺 ��ǥ
	int flipped_num = 0;// ���� �������� ī���� ����

	long start_time;// ���α׷� ���� �ð�
	long spent_time;// ���� �ð�
	long delay_time;// �ٷ� �ٽ� ? �� ���������� �ʵ��� �����̸� ��

	srand(time(0));

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
	text.setFillColor(Color::Black);
	text.setPosition(0, 0);
	char info[40];

	struct Card compare_card;// ù ��°�� ������ ī��
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
			// id�ʱ�ȭ ������, ���� �� id���� ���߿� �ֱ�
			cards[i][j].is_clicked = 0;
			cards[i][j].is_cleared = 0;// ���� ���� �ʾ����Ƿ� 0��
			n++;
		}
	}

	// ī�� 100�� ����
	for (int i = 0; i < 100; i++)
	{
		swap_card(&cards[rand() % row][rand() % row], &cards[rand()%row][rand()%row]);
	}

	// �ε����� ����id��, ��ġ ������
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < row; j++)
		{
			cards[i][j].id_i = i;
			cards[i][j].id_j = j;
			cards[i][j].sprite.setPosition(j*CARD_W, i*CARD_H);
		}
	}

	start_time = clock();
	delay_time = start_time;

	while (window.isOpen())
	{
		mouse_pos = Mouse::getPosition(window);// ���콺 ��ǥ �ǽð����� �ޱ�
		spent_time = clock() - start_time;

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
					for (int i = 0; i < row; i++)
					{
						for (int j = 0; j < row; j++)
						{
							// ���콺 ��ġ�� cards[i][j]�� ��ġ�� �ش��Ѵٸ�?
							if (cards[i][j].sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
							{
								// �������� ���� ī�常 �����ڴ�
								if ( cards[i][j].is_clicked == 0 )
								{
									cards[i][j].is_clicked = 1;// true
									flipped_num++;// �������� ī�� ����

									// �������� ī�尡 �� �����
									if (flipped_num == 1)
									{
										compare_card = cards[i][j];// ù ��° ī�带 ��ī��� ����
									}
									// �� ���� �������ٸ�
									else if (flipped_num == 2)
									{
										// ���� �� ī�尡 ���� ������
										if (compare_card.type == cards[i][j].type)
										{
											// ���� ī��� ����ī�尡 ������ �� �� �������� ��Ÿ��
											cards[i][j].is_cleared = 1;
											cards[compare_card.id_i][compare_card.id_j].is_cleared = 1;
										}
										// �� ī�尡 �ٸ� �����̸�
										else
										{
											delay_time = spent_time;
										}

									}
								}
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
				// Ŭ���� �� �����̰ų� ������ ���� ī���̸�
				if (cards[i][j].is_clicked == 1 || cards[i][j].is_cleared == 1 )
				{
					// �׸��� �ִ� ��������Ʈ�� ���� (ī�带 �����ڴٴ� �ǹ�)
					cards[i][j].sprite.setTexture(&t[cards[i][j].type]);
				}
				else
				{
					// ī��� ??? ����
					cards[i][j].sprite.setTexture(&t[0]);
				}
			}
		}

		// ���߿� �������
		// ������ ī�尡 2����� TODO : �� ��° ī��� �ٷ� �ٽ� ���������� �ʰ� �ϱ�
		if (flipped_num == 2)
		{
			// �� ī�尡 �������� 1�� �̳��� �ƴ϶��
			if (spent_time - delay_time <= 1000)
			{
			}
			else
			{
				for (int i = 0; i < row; i++)
					for (int j = 0; j < row; j++)
						cards[i][j].is_clicked = 0;
				// �� ������ ���·� ����� �����ڴ�
				flipped_num = 0;
			}
		}

		sprintf(info, "time: %d\n", spent_time/1000);
		text.setString(info);
		
		window.clear(Color::Black);
		
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < row; j++)
			{
				window.draw(cards[i][j].sprite);
			}
		}

		window.draw(text);

		window.display();
		
	}
	return 0;
}