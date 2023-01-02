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
	int is_clicked;// 눌렸는가
};

int main(void) {

	RenderWindow window(VideoMode(1200, 800), "AfterSchool2");// 화면 크기, 제목
	window.setFramerateLimit(60);// 60초마다 한 번씩 돌아간다

	// f : 소수
	// Vector2i : 정수
	Vector2i mouse_pos;// 마우스 좌표
	int flipped_num = 0;// 현재 뒤집혀진 카드의 갯수

	long start_time;// 프로그램 시작 시각
	long spent_time;// 현재 시각
	long delay_time;// 바로 다시 ? 로 뒤집혀지지 않도록 딜레이를 줌

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

	// 텍스트
	Text text;
	text.setFont(font);
	text.setCharacterSize(30);// 글자 크기
	text.setFillColor(Color::Black);
	text.setPosition(0, 0);
	char info[40];

	struct Card cards[row][row];
	int n = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < row; j++)
		{
			cards[i][j].sprite.setSize(Vector2f(CARD_W, CARD_H));
			cards[i][j].sprite.setPosition(j * CARD_W, i * CARD_H);// j가 커질수록 x값이 100증가, i가 커질수록 y값이 200증가
			cards[i][j].sprite.setTexture(&t[0]);// 뒤집는 그림이 0이기 때문에 1부터
			cards[i][j].type = 1 + n / 2;
			cards[i][j].id = n + 1;
			cards[i][j].is_clicked = 0;
			n++;
		}
	}

	start_time = clock();
	delay_time = start_time;

	while (window.isOpen())
	{
		mouse_pos = Mouse::getPosition(window);// 마우스 좌표 실시간으로 받기
		spent_time = clock() - start_time;

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
					for (int i = 0; i < row; i++)
					{
						for (int j = 0; j < row; j++)
						{
							// 마우스 위치가 cards[i][j]의 위치에 해당한다면?
							if (cards[i][j].sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
							{
								// 뒤집히지 않은 카드만 뒤집겠다
								if ( cards[i][j].is_clicked == 0 )
								{
									cards[i][j].is_clicked = 1;// true
									flipped_num++;// 뒤집혀진 카드 갯수
									// 두 개를 뒤집었다면
									if (flipped_num == 2)
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

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < row; j++)
			{
				// 클릭하면 카드 뒤집기
				if (cards[i][j].is_clicked == 1 )
				{
					// 그림이 있는 스프라이트로 변경 (카드를 뒤집겠다는 의미)
					cards[i][j].sprite.setTexture(&t[cards[i][j].type]);
				}
				else
				{
					// 카드는 ??? 상태
					cards[i][j].sprite.setTexture(&t[0]);
				}
			}
		}

		// 나중에 지울거임
		// 뒤집힌 카드가 2개라면 TODO : 두 번째 카드는 바로 다시 뒤집혀지지 않게 하기
		if (flipped_num == 2)
		{
			// 두 카드가 뒤집힌지 1초 이내가 아니라면
			if (spent_time - delay_time <= 1000)
			{
			}
			else
			{
				for (int i = 0; i < row; i++)
					for (int j = 0; j < row; j++)
						cards[i][j].is_clicked = 0;
				// 다 뒤집힌 상태로 만들어 버리겠다
				flipped_num = 0;
			}
		}

		sprintf(info, "(%d, %d) spent_time %d delay_time %d\n", mouse_pos.x, mouse_pos.y, spent_time/1000, delay_time/1000);
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