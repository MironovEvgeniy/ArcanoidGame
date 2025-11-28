#include "GameStateWin.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace ArcanoidGame
{
	void GameStateWinData::Init()
	{
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		timeSinceGameWin = 0.f;

		sf::Color backgroundColor = sf::Color::Black;
		backgroundColor.a = 200; // a means Alfa, opacity
		background.setFillColor(backgroundColor);

		gameWinText.setFont(font);
		gameWinText.setCharacterSize(48);
		gameWinText.setStyle(sf::Text::Bold);
		gameWinText.setFillColor(sf::Color::Red);
		gameWinText.setString("Winning!");
				
		hintText.setFont(font);
		hintText.setCharacterSize(24);
		hintText.setFillColor(sf::Color::White);
		hintText.setString("Do you want to start new game?");

		MenuItem yesItem;
		yesItem.text.setString("Yes");
		yesItem.text.setFont(font);
		yesItem.text.setCharacterSize(24);
		yesItem.onPressCallback = [](MenuItem&) {Application::Instance().GetGame().SwitchStateTo(GameStateType::Playing); };

		MenuItem noItem;
		noItem.text.setString("No");
		noItem.text.setFont(font);
		noItem.text.setCharacterSize(24);
		noItem.onPressCallback = [](MenuItem&) {Application::Instance().GetGame().SwitchStateTo(GameStateType::MainMenu); };

		MenuItem GameWinItem;
		GameWinItem.childrenOrientation = Orientation::Horizontal;
		GameWinItem.childrenAlignment = Alignment::Middle;
		GameWinItem.childrens.push_back(yesItem);
		GameWinItem.childrens.push_back(noItem);

		menu.Init(GameWinItem);
	}

	void GameStateWinData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				menu.PressOnSelectedItem();
			}

			Orientation orientation = menu.GetCurrentContext().childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				menu.SwitchToPreviousMenuItem();
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				menu.SwitchToNextMenuItem();
			}
		}
	}

	void GameStateWinData::Update(float timeDelta)
	{
		timeSinceGameWin += timeDelta;

		sf::Color gameWinTextColor = (int)timeSinceGameWin % 2 ? sf::Color::Blue : sf::Color::Yellow;
		gameWinText.setFillColor(gameWinTextColor);

	}

	void GameStateWinData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		background.setOrigin(0.f, 0.f);
		background.setSize(viewSize);
		window.draw(background);

		gameWinText.setOrigin(GetTextOrigin(gameWinText, { 0.5f, 1.f }));
		gameWinText.setPosition(viewSize.x / 2.f, viewSize.y / 2 - 150.f);
		window.draw(gameWinText);

		hintText.setOrigin(GetTextOrigin(hintText, { 0.5f, 1.f }));
		hintText.setPosition(viewSize.x / 2.f, viewSize.y / 2 - 50.f);
		window.draw(hintText);

		menu.Draw(window, window.getView().getCenter(), { 0.5f, 0.f });
	}
}