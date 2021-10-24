#include "Slider.hpp"

namespace mf
{
	Slider::Slider(/* args */)
	:mBackground(&mPos, &mSize)
	{
		component::EventManager	*manager = &mEventManager;
		mEventManager.AddEventListener(eEvent::LEFT_CLICK, [this, manager] {
			float	relpos = (manager->GetMousePosition().x - this->GetPosition().x) / (this->GetSize().x  - mButton->GetSize().x) - ((mButton->GetSize().x / 2.f) / this->GetSize().x);
			this->SetValue(relpos);
		});
	}

	Slider::~Slider()
	{
	}

	Slider      *Slider::Create()
	{
		Slider   *slider = new Slider();
		slider->SetSize(200, 40);
		slider->SetOutlineColor(sf::Color::Black)->SetOutlineThickness(1.f);
		slider->mButton = Button::Create(sf::Color::Red, sf::Color::Green);
		slider->mButton->SetSize(30, 40);
		slider->AddWidget(slider->mButton);
		slider->mButton->SetPosition(0, 0);
		return (slider);
	}

	void		Slider::Render(sf::RenderWindow *tWindow)
	{
		mBackground.Draw(tWindow);
		Widget::Render(tWindow);
	}

	void		Slider::HandleEvent(sf::Event &tEvent)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mEventManager.GetEvent() == eEvent::INSIDE)
			SetValue((mEventManager.GetMousePosition().x - this->GetPosition().x) / (this->GetSize().x  - mButton->GetSize().x) - ((mButton->GetSize().x / 2.f) / this->GetSize().x));
		Widget::HandleEvent(tEvent);
	}


	Slider		*Slider::SetValue(float tValue)
	{
		mValue = tValue;
		float newpos = tValue * (mSize.x - mButton->GetSize().x);
		newpos = std::clamp(newpos, 0.f, mSize.x - mButton->GetSize().x);
		mButton->SetPosition(newpos, 0);
		return (this);
	};

}
