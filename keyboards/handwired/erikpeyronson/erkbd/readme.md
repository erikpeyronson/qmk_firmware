# handwired/erikpeyronson/erkbd

![handwired/erikpeyronson/erkbd](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Erik Peyronson](https://github.com/erikpeyronson)
* Hardware Supported: rp2040 zero, 3d printer (i used stock creality ender 3v3 ke with default settings)
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make handwired/erikpeyronson/erkbd:default

Flashing example for this keyboard:

    make handwired/erikpeyronson/erkbd:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
