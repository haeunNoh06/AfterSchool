#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>

using namespace sf;

const int row = 4;
const int CARD_W = 200;
const int CARD_H = 200;

struct Card {
	RectangleShape sprite;
	int id;
};

int main(void) {

	RenderWindow window(VideoMode(1200, 800), "AfterSchool2");// ȭ�� ũ��, ����
	window.setFramerateLimit(60);// 60�ʸ��� �� ���� ���ư���

	// f : �Ҽ�
	// Vector2i : ����
	Vector2i mouse_pos;// ���콺 ��ǥ
	int click_cnt = 0;// ���콺 ���� Ƚ��

	// ��Ʈ
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
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < row; j++)
		{
			cards[i][j].sprite.setSize(Vector2f(CARD_W, CARD_H));
			cards[i][j].sprite.setPosition(j * CARD_W, i * CARD_H);// j�� Ŀ������ x���� 100����, i�� Ŀ������ y���� 200����
			cards[i][j].sprite.setFillColor(Color(i * 64, j * 64, 128));
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
					click_cnt++;
				}
			}
		}
		
		sprintf(info, "(%d, %d) clicks %d\n", mouse_pos.x, mouse_pos.y, click_cnt);
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