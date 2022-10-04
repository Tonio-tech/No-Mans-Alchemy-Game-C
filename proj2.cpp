//Title: Project 2: No Man's Alchemy
//Author: Toni Olafunmiloye
//Date: 3/10/2021
//Description: This is main for project 2

#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

int main () {
  srand(time(NULL));
  Game newGame;
  newGame.StartGame();
  return 0;
}
