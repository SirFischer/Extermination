#include "../../includes/mfGUI.hpp"

mf::Text	*text;
mf::Slider	*slider;

void CreateMainMenu()
{
	mf::GUI::ClearWidgets();

	
	mf::Image *img = mf::Image::Create("assets/photo-1542044896530-05d85be9b11a.jpeg");
	mf::GUI::AddWidget(img
	->SetSize(50.f, 50.f)
	->SetPosition(5.f, 20.f)
	->SetOutlineColor(sf::Color::Black)
	->SetOutlineThickness(3.f)
	->SetSizePercentage(true)
	->SetPositionPercentage(true));

	mf::Text	*textWidget = 
	mf::Text::Create("assets/Bangers-Regular.ttf", "This is a test text widget to test the text wrapping algorithm...")
	->SetPosition(30, 30)
	->SetSize(80, 80)
	->SetOutlineColor(sf::Color::Black)
	->SetOutlineThickness(1.0f)
	->SetTextColor(sf::Color::Black)
	->SetSizePercentage(true)
	->EnableEdit();
	img->AddWidget(textWidget);


	//LIST TEST
	mf::List	*listWidget = mf::List::Create();
	listWidget->SetPosition(60, 20)
	->SetPositionPercentage(true)
	->SetSize(35, 50)
	->SetSizePercentage(true)
	->SetBackgroundColor(sf::Color::Green)
	->SetItemDirection(mf::List::eListDirection::HORIZONTAL)
	->SetContentOverflow(mf::List::eOverflow::WRAP);
	mf::GUI::AddWidget(listWidget);

	mf::Button	*btn = mf::Button::Create(sf::Color::Black, sf::Color::White);
	listWidget->AddWidget(btn);

	mf::Button	*btn2 = mf::Button::Create(sf::Color::Black, sf::Color::White);
	btn2->SetSize(120, 50);
	listWidget->AddWidget(btn2);

	mf::Button	*btn3 = mf::Button::Create(sf::Color::Black, sf::Color::White);
	listWidget->AddWidget(btn3);

	mf::Button	*btn4 = mf::Button::Create(sf::Color::Black, sf::Color::White);
	btn4->SetSize(110, 30);
	listWidget->AddWidget(btn4);

	mf::Button	*btn5 = mf::Button::Create(sf::Color::Black, sf::Color::White);
	listWidget->AddWidget(btn5);

	slider = mf::Slider::Create();
	slider->SetPosition(70, 80)->SetPositionPercentage(true);
	mf::GUI::AddWidget(slider);

	text = mf::Text::Create("assets/Bangers-Regular.ttf", std::to_string(slider->GetValue()));
	text->SetPosition(85, 80)->SetPositionPercentage(true);
	text->SetTextColor(sf::Color::Black);
	mf::GUI::AddWidget(text);
}

int main()
{
	sf::RenderWindow	window(sf::VideoMode(1600, 900), "Sandbox", sf::Style::Default);
	mf::GUI::Init(&window);
	bool	isOpen = true;

	CreateMainMenu();

	int fps = 0;
	sf::Clock fpsClock;
	while (isOpen)
	{
		fps++;
		if (fpsClock.getElapsedTime().asSeconds() > 1.0)
		{
			std::cout << "FPS: " << fps << std::endl;
			fps = 0;
			fpsClock.restart();
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				isOpen = false;
			std::cout << event.type << std::endl;
			if (event.type == sf::Event::Resized)
			{
				window.setView(sf::View(sf::Vector2f(event.size.width / 2, event.size.height / 2), sf::Vector2f(window.getSize())));
			}
			mf::GUI::HandleEvent(event);
			text->SetText(std::to_string(std::clamp(slider->GetValue(), 0.f, 1.f)));
		}
		window.clear(sf::Color::White);
		mf::GUI::Render();
		window.display();
	}
	window.close();
	mf::GUI::ClearWidgets();
}