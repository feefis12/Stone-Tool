/*
  ==============================================================================

    ClickSlider.cpp
    Created: 23 Jan 2021 6:46:28pm
    Author:  Felix

  ==============================================================================
*/

#include "ClickSlider.h"

MySlider::MySlider()
{
	choice = 0;
}



void MySlider::mouseDown(const MouseEvent& e)
{

	ModifierKeys modifiers = ModifierKeys::getCurrentModifiersRealtime();
	// check the mod keys ..
	if (modifiers.isPopupMenu() || modifiers.isCtrlDown())
	{
		int result = 0;
		p->clear();
		p->addItem(1, "Invert", true, false);
		p->show(1, 100, 100, 100, nullptr);
		result = p->show();
		if (result != 0)
		{
			if (result == 1)
			{
				choice = 1;
			}
		}

		
	}
	else
	{
		Slider::mouseDown(e);   // to the usual thing .... drag the slider
	}
}

float MySlider::returnInvert()
{
	if (choice == 1)
	{
		return 1;
	}
	
}
