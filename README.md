# ![image](https://github.com/mbnatafgi/EECE435LProject/raw/master/images/bomb-small.png) Welcome to EECE435L Project! ![image](https://github.com/mbnatafgi/EECE435LProject/raw/master/images/baby-small.png)

This is a course project that we worked on back in the days when I started learning programming, so **do not expect any best practices!**

## Description
This project is composed of two games that users have the option to sign up prior to playing or simply play as guests. The benefit of signing up is to allow pausing and resuming a game, record previous gameplay scores, and unlock new difficulties. Cool, right?  

Now that I got you interested, it's time to run it and get amazed by the stunning graphics. I'm kidding, it is 2D and non-responsive, but I'll leave it up to you to judge!

## Installation
We used C++ and Qt5 for designing the UI and the games' scenes. So, you need the Qt headers to be able to build and run.

> For this guide, I assume your machine is running a debian-based linux distro. If it doesn't, please try to follow some external guides to install Qt.

Start off by installing build-essentials in case you don't already have it installed: 
```
sudo apt-get install build-essential
```
Next, we install qtcreator:
```
sudo apt-get install qtcreator
```
Finally, we set Qt5 as the default:
```
sudo apt-get install qt5-default
```
We should now have ```qmake``` at our fingertips to build the project, you can do that with:
```
qmake Project435.pro
```
This will generate a Makefile that we can build using:
```
make
```
After ```make``` has run without errors we can run the executable with:
```
./Project435
```

You can now start playing!

Game 1
![image](https://github.com/mbnatafgi/EECE435LProject/raw/master/images/game1.png)

Game 2
![image](https://github.com/mbnatafgi/EECE435LProject/raw/master/images/game2.png)

