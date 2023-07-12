#pragma once

#include <SFML/Graphics.hpp>

#include <string>

const std::string       windowName                  =       "_test_";
const bool              fullscreen                  =       false;
const int               fpsLimit                    =       60;
const bool              vSync                       =       true;
const int               textSize                    =       75;
const sf::Color         textColor                   =       sf::Color(160, 160, 160, 191);
const int               blinksPerSecond             =       2;

const int               startUps                    =       25;
const int               upsChangeStrength           =       5;
const int               width                       =       1600;
const int               height                      =       800;
const int               size                        =       10;
const float             zoomStrength                =       0.1;
const float             minZoom                     =       0.1;
const float             maxZoom                     =       10;     

const int               underpopulation_bound       =       2;
const int               overpopulation_bound        =       3;
const int               reproduction_bound          =       3;
const int               dx[]                        =       {  -1, 0,  1,  -1, 1,  -1, 0,  1   };
const int               dy[]                        =       {  -1, -1, -1, 0,  0,  1,  1,  1   };