#pragma once
#include "Windows.Xbox.Graphics.Display.DisplayConfiguration.g.h"

// WARNING: This file is automatically generated by a tool. Do not directly
// add this file to your project, as any changes you make will be lost.
// This file is a stub you can use as a starting point for your implementation.
//
// To add a copy of this file to your project:
//   1. Copy this file from its original location to the location where you store 
//      your other source files (e.g. the project root). 
//   2. Add the copied file to your project. In Visual Studio, you can use 
//      Project -> Add Existing Item.
//   3. Delete this comment and the 'static_assert' (below) from the copied file.
//      Do not modify the original file.
//
// To update an existing file in your project:
//   1. Copy the relevant changes from this file and merge them into the copy 
//      you made previously.
//    
// This assertion helps prevent accidental modification of generated files.


namespace winrt::Windows::Xbox::Graphics::Display::implementation
{
    struct DisplayConfiguration : DisplayConfigurationT<DisplayConfiguration>
    {
        DisplayConfiguration() = default;

        static winrt::Windows::Xbox::Graphics::Display::DisplayConfiguration GetForCurrentView();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Graphics::Display::DisplayMode> SupportedDisplayModes();
        winrt::Windows::Xbox::Graphics::Display::DisplayMode CurrentDisplayMode();
        winrt::Windows::Foundation::IAsyncOperation<bool> RestoreDefaultDisplayModeAsync();
        winrt::Windows::Foundation::IAsyncOperation<bool> RequestSetCurrentDisplayModeAsync(winrt::Windows::Xbox::Graphics::Display::DisplayMode mode);
        void SetAdvancedData(winrt::Windows::Storage::Streams::IBuffer const& buffer);
    };
}
namespace winrt::Windows::Xbox::Graphics::Display::factory_implementation
{
    struct DisplayConfiguration : DisplayConfigurationT<DisplayConfiguration, implementation::DisplayConfiguration>
    {
    };
}