#pragma once
#include "Windows.Xbox.Media.GameTransportControls.g.h"

namespace winrt::Windows::Xbox::Media::implementation
{
	struct GameTransportControls : GameTransportControlsT<GameTransportControls>
	{
		GameTransportControls() = default;

		hstring Title();
		hstring Subtitle();
		winrt::Windows::Xbox::Media::GamePlaybackStatus PlaybackStatus();
		void PlaybackStatus(winrt::Windows::Xbox::Media::GamePlaybackStatus const& value);
		winrt::Windows::Xbox::Media::SoundLevel SoundLevel();
		bool IsEnabled();
		void IsEnabled(bool value);
		bool IsPlayEnabled();
		void IsPlayEnabled(bool value);
		bool IsPauseEnabled();
		void IsPauseEnabled(bool value);
		bool IsMenuEnabled();
		void IsMenuEnabled(bool value);
		bool IsViewEnabled();
		void IsViewEnabled(bool value);
		bool IsBackEnabled();
		void IsBackEnabled(bool value);
		winrt::event_token ButtonPressed(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Media::GameTransportControls, winrt::Windows::Xbox::Media::GameTransportControlsButtonPressedEventArgs> const& handler);
		void ButtonPressed(winrt::event_token const& token) noexcept;
		winrt::event_token PropertyChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Media::GameTransportControls, winrt::Windows::Xbox::Media::GameTransportControlsPropertyChangedEventArgs> const& handler);
		void PropertyChanged(winrt::event_token const& token) noexcept;
	};
}
