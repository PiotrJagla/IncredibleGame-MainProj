#pragma once
class PopUpText
{
private:
	Timer* m_popUpTimer;
	sf::Font* m_textFont;
	sf::Text* m_popUpText;

	bool m_isTextShown;

public:
	PopUpText(float delay = 1000.0f);
	~PopUpText();

	void update(float& timePerFrame);
	void render(sf::RenderTarget* target);

	void showText(std::string textToShow, float delay);
	void hideText(float& timePerFrame);
};

