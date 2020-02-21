#pragma once

int menuMain();
int getKey();
void handleMenu(int key);
void printMenu(int menuID);
void printCurrentMenu();
void navigateTo(int);
void decreaseTime(void);
void increaseTime(void);
void selectStation(void);
void recordAudio(void);
void selectSong(void);
void confirmFlipBoolean(void);
void confirm(void);
char** menuText(int);