#include "pch.h"
#include "Windows.Xbox.Media.GameTransportControlsPropertyChangedEventArgs.h"
#include "Windows.Xbox.Media.GameTransportControlsPropertyChangedEventArgs.g.cpp"

namespace winrt::Windows::Xbox::Media::implementation
{
	winrt::Windows::Xbox::Media::GameTransportControlsProperty GameTransportControlsPropertyChangedEventArgs::Property()
	{
		GameTransportControlsProperty prop{};

		return prop;
	}
}
