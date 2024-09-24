#pragma once
#include "Windows.Xbox.Media.GameTransportControlsPropertyChangedEventArgs.g.h"

namespace winrt::Windows::Xbox::Media::implementation
{
	struct GameTransportControlsPropertyChangedEventArgs : GameTransportControlsPropertyChangedEventArgsT<GameTransportControlsPropertyChangedEventArgs>
	{
		GameTransportControlsPropertyChangedEventArgs() = default;

		winrt::Windows::Xbox::Media::GameTransportControlsProperty Property();
	};
}
