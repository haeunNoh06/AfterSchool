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
			}
		}

		printf("%d, %d", mouse_pos.x, mouse_pos.y);// ���콺 x�� y�� ���
	}

	return 0;
}