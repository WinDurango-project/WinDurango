# XBOXEmu
The worlds first Xbox One compatibility layer for Windows.

# HOW IT WORKS
The idea for this project is to provide a compatiability layer allowing you run binaries compiled for the Xbox One Development Kit (XDK).
How it works, we are implementing a basic Windows Portable Executable (Windows PE) loader that will load the .exe for Xbox One application.
In theory and more investigation is need the binary should be almost identifical if not identical to a Windows binary.
So we can make a basic PE loader that will load the binary and replace all the Xbox specific imports with Windows alternatives or reimplementations.

![Process](https://user-images.githubusercontent.com/1505374/213362181-869519f4-1920-4c3b-bb1b-364207d79e25.png)

# STATE
Currently as far as I am aware the are no Xbox One games that have been dump and decrypted. 
You can learn more about the Xbox One game format [here](https://xosft.dev/wiki/xbox-virtual-drive/).
You can however run applications that are compiled by the XDK or if they have been dumped and decrypted.
At this time nothing currently "boots", this compatiablitly layer is in early development.
This is like my fifth implementation and I think this is a good framework to make progress.
So I don't see anytime in the future to being able to run retail games and unless there is a major leak in keys or decrypted dumps.
However we can still run homebrew applications written using the XDK are loose and not bundle and decrypted allowing people to get into Xbox One development.

# FUTURE
In the future I would like to rewrite the PE loader instead using the one from the [aaaddress1](https://github.com/aaaddress1).
However my knowledge is limited and this was a good starting point for me to get started.

# CONTRIBUTION
I am looking for Contributors for this project. My Windows internal and Direct3D knowledge is limited.

# REFERENCES

Thank you to [aaaddress1](https://github.com/aaaddress1) for his Windows PE Loader [RunPE-In-Memory](https://github.com/aaaddress1/RunPE-In-Memory).
