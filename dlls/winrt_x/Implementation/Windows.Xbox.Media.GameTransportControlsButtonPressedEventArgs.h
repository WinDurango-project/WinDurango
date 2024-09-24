#pragma once
#include "Windows.Xbox.Media.GameTransportControlsButtonPressedEventArgs.g.h"

namespace winrt::Windows::Xbox::Media::implementation
{
	struct GameTransportControlsButtonPressedEventArgs : GameTransportControlsButtonPressedEventArgsT<GameTransportControlsButtonPressedEventArgs>
	{
		GameTransportControlsButtonPressedEventArgs() = default;

		winrt::Windows::Xbox::Media::GameTransportControlsButton Button();
	};
}
