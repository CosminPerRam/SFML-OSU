
# OSU-SFML-CPP
A very barebones copy of the [Osu!](osu.ppy.sh) game made in C++ 17 using SFML and based on the @Hopson97's [game framework](https://github.com/Hopson97/SFML-Game-Framework). 
This project is not intended to be a remake of the entire game in C++, it's more like a challenge project. I'm not a good programmer whatsoever so I'll implement what I can and how I can, feel free to open a ticket regarding _any_ topic.

## Status
 - The game supports reading Osu! beatmaps and provides _extremly_ basic gameplay mechanics for them.

## Dependencies
 - [SFML-2.5.1](https://www.sfml-dev.org)
 - [nlohmann](https://github.com/nlohmann/json)
 - [imgui](https://github.com/ocornut/imgui) (and the sfml support)
 - [lzma](https://docs.python.org/3/library/lzma.html)
 - [mpg123](https://www.mpg123.de)
 - [thor](https://bromeon.ch/libraries/thor/index.html)

## Others
 - [@HaselLoyance](https://github.com/HaselLoyance)'s [OsuParser](https://github.com/HaselLoyance/osu-parser) (modified)
 - @MickaGL's [SFML MP3 Player Extension](https://github.com/SFML/SFML/wiki/Source%3A-MP3-Player)
 - [@chen0040](https://github.com/chen0040)'s [Spline library](https://github.com/chen0040/cpp-spline) (modified)

## Releases
Head over to [releases](https://github.com/CosminPerRam/SFML-OSU/releases) to check out the latest release!

## Setup
**Note**: As of this readme commit, I have tried building the project only on Windows, i will look into trying this on Linux, but thats for another time. I also don't know yet if I will make a compile guide for this project but here are a few rough steps:
1. You need to compile the project using the dependencies above
2. After you get your executable, you need to create a few folders and get a few resources:
= create a "res" folder inside the executable's folder
= create "fonts", "maps", ~~"sfx", "textures"~~ inside the "res" folder
= get your favorite font, place it "fonts" and change its name to "default.ttf"
= copy your maps folder inside "maps" (*duh*)

## License
Use what you want and how you want but mentioning this repo would be nice.