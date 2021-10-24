#pragma once

#include "Widget.hpp"

namespace mf
{
	class List : public Widget
	{
	public:
		enum class eListDirection
		{
			HORIZONTAL,
			VERTICAL
		};

		enum class eOverflow
		{
			NOWRAP,
			WRAP,
			INVISIBLE
		};
	
	private:
		List(/* args */);
		~List();

		/**
		 * Components
		 **/
		component::Background  	mBackground;

		/**
		 * Type specific vars
		 **/
		eListDirection	mListDirection = eListDirection::VERTICAL;
		eOverflow		mOverflow = eOverflow::NOWRAP;
		float			mItemSpacing = 5.f;
		sf::Vector2f	mContentPosition = sf::Vector2f(0, 0);

		void			UpdateChildren();

	public:
		static List		*Create();

		void			Render(sf::RenderWindow	*tWindow);

		/**
		 * Setters
		 **/

		List			*SetDisabled(bool tDisabled){mDisabled = tDisabled; return (this);}
		
		//Transform
		List			*SetPosition(sf::Vector2f tPos){Widget::SetPosition(tPos); return (this);}
		List			*SetPosition(float tX, float tY){Widget::SetPosition(tX, tY); return (this);}
		List			*SetSize(sf::Vector2f tSize){Widget::SetSize(tSize); return (this);}
		List			*SetSize(float tX, float tY){Widget::SetSize(tX, tY); return (this);}
		List			*SetSizePercentage(bool tPercentage) {Widget::SetSizePercentage(tPercentage); return (this);}
		List			*SetPositionPercentage(bool tPercentage) { Widget::SetPositionPercentage(tPercentage); return (this);}

		//Background
		List			*SetBackgroundColor(sf::Color tColor) {mBackground.SetBackground(tColor); return (this);}
		List			*SetOutlineThickness(float tThickness) {mBackground.SetOutlineThickness(tThickness); return (this);}
		List			*SetOutlineColor(sf::Color tColor){mBackground.SetOutlineColor(tColor); return (this);}

		//List
		List			*SetItemSpacing(float tSpacing) {mItemSpacing = tSpacing; return (this);}
		List			*SetItemDirection(eListDirection tDirection) {mListDirection = tDirection; return (this);}
		List			*SetContentOverflow(eOverflow tOverflow) {mOverflow = tOverflow; return (this);}
		List			*SetContentPosition(sf::Vector2f tPos){mContentPosition = tPos; return (this);}

	};
}
