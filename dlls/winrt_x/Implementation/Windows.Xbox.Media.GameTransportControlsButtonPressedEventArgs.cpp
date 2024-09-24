#include "pch.h"
#include "Windows.Xbox.Media.GameTransportControlsButtonPressedEventArgs.h"
#include "Windows.Xbox.Media.GameTransportControlsButtonPressedEventArgs.g.cpp"

namespace winrt::Windows::Xbox::Media::implementation
{
	winrt::Windows::Xbox::Media::GameTransportControlsButton GameTransportControlsButtonPressedEventArgs::Button()
	{
		GameTransportControlsButton button{};

		return button;
	}
}
