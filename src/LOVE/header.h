unsigned long lastUpdate = 0; 
const int interval = 500; 
const int fadeAmount = 50; 

const CRGB colorLove = CRGB::Red;
const int Love[][2] = { { 4, 4 }, { 5, 3 }, { 5, 4 }, { 5, 5 }, { 6, 2 }, { 6, 3 }, { 6, 4 }, { 6, 5 }, { 7, 1 }, { 7, 2 }, { 7, 3 }, { 7, 4 }, { 8, 2 }, { 8, 3 }, { 8, 4 }, { 8, 5 }, { 9, 3 }, { 9, 4 }, { 9, 5 }, { 10, 4 } };
const int numLove = sizeof(Love) / sizeof(Love[0]);

const CRGB H_COLOR = CRGB::Red;
const int H_LOCATION[][2] = { { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 2, 3 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 } };
const int num_H = sizeof(H_LOCATION) / sizeof(H_LOCATION[0]);

const CRGB E_COLOR = CRGB::Orange;
const int E_LOCATION[][2] = { { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 }, { 5, 1 }, { 5, 3 }, { 5, 5 }, { 6, 1 }, { 6, 3 }, { 6, 5 } };
const int num_E = sizeof(E_LOCATION) / sizeof(E_LOCATION[0]);

const CRGB L_COLOR = CRGB::SkyBlue;
const int L_LOCATION[][2] = { { 7, 1 }, { 7, 2 }, { 7, 3 }, { 7, 4 }, { 7, 5 }, { 8, 1 } };
const int num_L = sizeof(L_LOCATION) / sizeof(L_LOCATION[0]);

const CRGB l_COLOR = CRGB::Navy;
const int l_LOCATION[][2] = { { 9, 1 }, { 9, 2 }, { 9, 3 }, { 9, 4 }, { 9, 5 }, { 10, 1 } };
const int num_l = sizeof(l_LOCATION) / sizeof(l_LOCATION[0]);

const CRGB O_COLOR = CRGB::Green;
const int O_LOCATION[][2] = { { 11, 1 }, { 11, 2 }, { 11, 3 }, { 11, 4 }, { 11, 5 }, { 12, 1 }, { 12, 5 }, { 13, 1 }, { 13, 2 }, { 13, 3 }, { 13, 4 }, { 13, 5 } };
const int num_O = sizeof(O_LOCATION) / sizeof(O_LOCATION[0]);