#ifndef _INC_MAGICNUMBERS_H

#define _INC_MAGICNUMBERS_H

// Used for bit-calculations: 2^N
const int k_exponents[11] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

// Betting rounds
const int k_number_of_betrounds = 4;
const int k_betround_preflop	= 1;
const int k_betround_flop		= 2;
const int k_betround_turn		= 3;
const int k_betround_river		= 4;

// Number of players
const int k_max_number_of_players = 10;

// Number of cards
const int k_number_of_community_cards  = 5;
const int k_number_of_cards_per_player = 2;

// Game type
const int k_gametype_unknown = -1;
const int k_gametype_NL      =  0;
const int k_gametype_PL  	 =  1;
const int k_gametype_FL      =  2;

//  File accessable?
//  (<unistd.h> is not contained in MSCVPP)
const int F_OK = 0;


#endif // _INC_MAGICNUMBERS_H
