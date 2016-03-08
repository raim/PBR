# Open and Modular Photobioreactor for Quantiative and Theoretical Biology

* Code repository for a modular photobioreactor, based on arduino
and raspberry pi controlled sensor and control devices. 
* Initiated at the 1st QTB PBR Hack`a'thing, March 2-4 2016, at the
Quantitative and Theoretical Biology Group of the Heinrich-Heine
University Düsseldorf. See
[QTB wiki page](https://wiki.hhu.de/display/QTBP/1st+QTB+PBR+Hack%60a'thing).
* Inspired by prior work from Dougie B. Murray and Rob Lehmann, fuelled by
the DIY spirit.


# SET-UP ARDUINO & LIBRARIES

## Installing Arduino IDE

1. E.g., on Fedora: `sudo dfl install arduino` or on Ubuntu/Debian: `sudo apt-get install arduino arduino-core`
2. Running `arduino` requires permissions to communicate with the USB port; this will either be managed by the software `arduino`, which will prompt you for a root password to add you to dialout and tty groups, or you can do it manually (on commmand-line) with `sudo usermod -a -G tty yourUserName; sudo usermod -a -G dialout yourUserName`. To take effect you'll need to logout and login again. 
3. To access this ocde (`PBR/code`) from the `arduino` IDE easily, you can simply add a symbolic link to arduino's sketchbook directory, e.g. by `ln -s ~/programs/PBR/code ~/sketchbook`

## Using Emacs for Arduino Code
i. Download [emacs mode (arduino-mode.el)](https://github.com/bookest/arduino-mode), e.g., to ~/.emacs.d/lisp
ii. Add the following code to your ~/.emacs file:
```
;; adding local .el files
(add-to-list 'load-path "~/.emacs.d/lisp")
(progn (cd "~/.emacs.d/lisp")
       (normal-top-level-add-subdirs-to-load-path))
;; auto-recognize arduino files via file-ending:
(setq auto-mode-alist (cons '("\\.\\(pde\\|ino\\)$" . arduino-mode) auto-mode-alist))
(autoload 'arduino-mode "arduino-mode" "Major mode for editing Arduino." t)
```
iii. In the `arduino` IDE activate "Use External Editor" in File > Preferences

## Installing Required Libraries

There are two+ ways to install additional libraries for Arduino. Either download
a .zip file of the library and import them via the `arduino` IDE (`Import Library > Add Library` and select the .zip file), or unpack (or e.g. git clone) them into your local arduino library path (e.g., ~/sketchbook/libraries). The latter
requires closing and re-opening the `arduino` IDE.

* Touch screen: Our common module control is via the Arduino Mega 2560 board with Sainsmart's touch screen (SSD1289). These work with [Rinky-Dink's libraries](http://www.rinkydinkelectronics.com/). Download `UTFT.zip`, `UTFT_Buttons.zip` and `UTouch.zip` and install them via the `arduino` IDE's .zip file import.
* [Time library](https://github.com/PaulStoffregen/Time)
* [HX711 library](https://github.com/bogde/HX711) for the scale module (liqometer)

