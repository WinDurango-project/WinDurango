#include "pch.h"
#include "Windows.Xbox.Media.GameTransportControls.h"
#include "Windows.Xbox.Media.GameTransportControls.g.cpp"

namespace winrt::Windows::Xbox::Media::implementation
{
	hstring GameTransportControls::Title()
	{
		return L"Example Title";
	}

	hstring GameTransportControls::Subtitle()
	{
		return L"Example Subtitle";
	}

	winrt::Windows::Xbox::Media::GamePlaybackStatus GameTransportControls::PlaybackStatus()
	{
		return GamePlaybackStatus::Stopped;
	}

	void GameTransportControls::PlaybackStatus(winrt::Windows::Xbox::Media::GamePlaybackStatus const& value)
	{
		
	}

	winrt::Windows::Xbox::Media::SoundLevel GameTransportControls::SoundLevel()
	{
		return SoundLevel::Full;
	}

	bool GameTransportControls::IsEnabled()
	{
		return TRUE;
	}

	void GameTransportControls::IsEnabled(bool value)
	{
		
	}

	bool GameTransportControls::IsPlayEnabled()
	{
		return TRUE;
	}

	void GameTransportControls::IsPlayEnabled(bool value)
	{

	}

	bool GameTransportControls::IsPauseEnabled()
	{
		return TRUE;
	}

	void GameTransportControls::IsPauseEnabled(bool value)
	{

	}

	bool GameTransportControls::IsMenuEnabled()
	{
		return TRUE;
	}

	void GameTransportControls::IsMenuEnabled(bool value)
	{
		
	}

	bool GameTransportControls::IsViewEnabled()
	{
		return TRUE;
	}

	void GameTransportControls::IsViewEnabled(bool value)
	{
		
	}

	bool GameTransportControls::IsBackEnabled()
	{
		return TRUE;
	}

	void GameTransportControls::IsBackEnabled(bool value)
	{
		
	}

	winrt::event_token GameTransportControls::ButtonPressed(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Media::GameTransportControls, winrt::Windows::Xbox::Media::GameTransportControlsButtonPressedEventArgs> const& handler)
	{
		event_token et{};

		return et;
	}

	void GameTransportControls::ButtonPressed(winrt::event_token const& token) noexcept
	{
		
	}

	winrt::event_token GameTransportControls::PropertyChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Media::GameTransportControls, winrt::Windows::Xbox::Media::GameTransportControlsPropertyChangedEventArgs> const& handler)
	{
		event_token et{};

		return et;
	}

	void GameTransportControls::PropertyChanged(winrt::event_token const& token) noexcept
	{
		
	}
}
