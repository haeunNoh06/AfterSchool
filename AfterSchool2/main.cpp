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

	RenderWindow window(VideoMode(1200, 800), "AfterSchool2");// 화면 크기, 제목
	window.setFramerateLimit(60);// 60초마다 한 번씩 돌아간다

	// f : 소수
	// Vector2i : 정수
	Vector2i mouse_pos;// 마우스 좌표
	int click_cnt = 0;// 마우스 누른 횟수

	// 폰트
	Font font;
	font.loadFromFile("c:/Windows/Fonts/arial.ttf");

	// 텍스트
	Text text;
	text.setFont(font);
	text.setCharacterSize(30);// 글자 크기
	text.setFillColor(Color::White);
	text.setPosition(0, 0);
	char info[40];

	struct Card cards[row][row];
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < row; j++)
		{
			cards[i][j].sprite.setSize(Vector2f(CARD_W, CARD_H));
			cards[i][j].sprite.setPosition(j * CARD_W, i * CARD_H);// j가 커질수록 x값이 100증가, i가 커질수록 y값이 200증가
			cards[i][j].sprite.setFillColor(Color(i * 64, j * 64, 128));
		}
	}

	while (window.isOpen())
	{
		mouse_pos = Mouse::getPosition(window);// 마우스 좌표 실시간으로 받기

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			// 한 번 누르면 한 번만 적용
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