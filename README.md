# LuaBird

Wanted to learn how to the C++ Lua API, so I threw this masterpiece together.

The C++ side creates a "Sprite" usertype, that allows the creation of the game.

The main loop in the C++ calls the "update" function defined in the Lua code once per frame for updating, and then iterates through a global Sprite table (defined in the lua `game/_lib.lua`) for rendering.

Screenshot:

![Image of gameplay](https://i.imgur.com/aRQ7yhH.png)

## Building and Running

### Libraries

SFML is required.

These can be installed from your project manager. For example, on Debian/ Ubuntu:

```sh
sudo apt install libsfml-dev
```

If this is not possible (eg windows), you can install these manually from their respective websites:

https://www.sfml-dev.org/download.php

### Linux

To build, at the root of the project:

```sh
sh scripts/build.sh
```

To run, at the root of the project:

```sh
sh scripts/run.sh
```

To build and run in release mode, simply add the `release` suffix:

```sh
sh scripts/build.sh release
sh scripts/run.sh release
```

You can also create a deployable build (that can be sent) by doing:

```sh
sh scripts/deploy.sh
```
