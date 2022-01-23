//
// Copyright(C) 2022 by Ryan Krafnick
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	DSDA MapInfo Legacy
//

#ifndef __DSDA_MAPINFO_LEGACY__
#define __DSDA_MAPINFO_LEGACY__

int dsda_LegacyNextMap(int* episode, int* map);
int dsda_LegacyShowNextLocBehaviour(int* behaviour);
int dsda_LegacySkipDrawShowNextLoc(int* skip);
void dsda_LegacyUpdateMapInfo(void);
void dsda_LegacyUpdateLastMapInfo(void);
void dsda_LegacyUpdateNextMapInfo(void);
int dsda_LegacyResolveCLEV(int* clev, int* episode, int* map);
int dsda_LegacyMapMusic(int* music_index, int* music_lump);
int dsda_LegacyInterMusic(int* music_index, int* music_lump);

#endif
