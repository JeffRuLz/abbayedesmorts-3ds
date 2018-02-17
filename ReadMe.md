# Abbaye-3DS

3DS port of the indie game *l'Abbaye des Morts* by Locomalito. It's written in C using the libctru and citro3d
libraries.

It's a modification of the linux port by nevat. [Link](https://github.com/nevat/abbayedesmorts-gpl)

## Another Abbaye des Morts port for 3DS?

Abbaye des Morts has already been ported to the 3DS by Nop90. It's based on an old version of the linux port and uses his port of SDL 1.2.
Unfortunately, it runs at half speed (For me, at least.) This is unacceptable for an already slow game.
I first tried to fix his port and find the source of the slowdown but nothing I tried worked. So I decided to restart and port the game again.

I based this port on the latest source code of the linux version. It has been re-written, uses SDL 2, and fixed a few issues.
For this 3DS port, I replaced the SDL code with Citro3D and standard 3DS code. You can now play Abbaye des Morts at full speed on your 3DS!

## History

[Abbaye des Morts](https://www.locomalito.com/abbaye_des_morts.php) is a freeware game
made by LocoMalito (with the help of Gryzor87 for Music and FX) in 2010. It was developed
with Gamemaker and only runs natively in Microsoft Windows systems.

This is a port to GNU/Linux systems and any system that supports C and SDL libraries.

The version 2.0 of the game is a port from SDL1.2 to SDL2 libraries. This includes a nice
set of features: OpenGL rendering, auto-scaling, Android & IOS support, VSync, etc.

This 3DS version is based on version 2.0, but with the SDL2 functions replaced with standard 3DS ones.

## License

The code is licensed under the GNU GPL version 3, see COPYING file for reference. Anyone
can download, see, change and redistribute the code.
The Graphics and Sounds have been released under the CC-BY-3.0 license.
