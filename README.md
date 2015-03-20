
sACN Discovery is a very simple GUI that uses the new discovery mechanism in
E1.31 (sACN) to display a list of sACN sources.

Once you have OLA installed, you can run;

$ qmake
$ make

If you're building from Qt Creator, you'll probably need to edit the Project's
Build settings and set PKG_CONFIG_PATH and PATH to the correct values.

Also if you get undefined reference warnings, see :

http://blog.inventic.eu/2014/01/qt-on-osx-maverick-undefined-symbols-for-architecture-x86_64/
http://stackoverflow.com/questions/20342896/solved-qt5-1-qt5-2-mac-os-10-9-mavericks-xcode-5-0-2-undefined-symbols

Edit the .pro file, and add:

  QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9

Then run qmake && make clean && make     
