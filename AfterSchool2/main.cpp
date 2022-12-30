#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>

using namespace sf;

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

		window.display();
		
	}
	return 0;
}