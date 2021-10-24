#include "List.hpp"

namespace mf
{
	List::List(/* args */)
	:mBackground(&mPos, &mSize)
	{
		
	}

	List::~List()
	{
	}

	List      *List::Create()
	{
		List   *list = new List();
		return (list);
	}

	void		List::Render(sf::RenderWindow *tWindow)
	{
		UpdateChildren();
		mBackground.Draw(tWindow);
		Widget::Render(tWindow);
	}

	void		List::UpdateChildren()
	{
		Widget	*lastWidget = NULL;
		float offset = 0;
		float maxOffset = 0;
		for (auto &child : mWidgets)
		{
			
			if ((child->GetSize().x > maxOffset && mListDirection == eListDirection::VERTICAL) ||
				(child->GetSize().y > maxOffset && mListDirection == eListDirection::HORIZONTAL))
				maxOffset = (mListDirection == eListDirection::VERTICAL) ? child->GetSize().x : child->GetSize().y;
			if (mListDirection == eListDirection::VERTICAL)
			{
				if (((lastWidget) ? lastWidget->GetPosition().y + lastWidget->GetSize().y + mItemSpacing : 0) + child->GetSize().y + mContentPosition.y > mSize.y + mPos.y   && mOverflow == eOverflow::WRAP)
				{
					if (maxOffset != 0 && lastWidget)
					{
						offset += maxOffset + mItemSpacing;
						lastWidget = NULL;
					}
					maxOffset = 0;
				}
				child->SetPosition(mContentPosition.x + offset, ((lastWidget) ? lastWidget->GetRelativePosition().y + lastWidget->GetSize().y : 0) + mItemSpacing + mContentPosition.y);
			}
			else
			{
				if (((lastWidget) ? lastWidget->GetPosition().x + lastWidget->GetSize().x + mItemSpacing : 0) + child->GetSize().x + mContentPosition.x > mSize.x + mPos.x && mOverflow == eOverflow::WRAP)
				{
					if (maxOffset != 0 && lastWidget)
					{
						offset += maxOffset + mItemSpacing;
						lastWidget = NULL;
					}
					maxOffset = 0;
				}
				child->SetPosition(((lastWidget) ? lastWidget->GetRelativePosition().x + lastWidget->GetSize().x : 0) + mItemSpacing + mContentPosition.x, mContentPosition.y + offset);
			}
			lastWidget = child;
		}
	}

}
