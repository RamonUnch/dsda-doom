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
//	DSDA Thing ID
//

#include "thing_id.h"

#define THING_ID_HASH_MAX 128

static thing_id_list_t* thing_id_list_hash[THING_ID_HASH_MAX];

static thing_id_list_t* dsda_NewThingIDList(short thing_id) {
  thing_id_list_t* result;

  result = calloc(1, sizeof(*result));
  result->thing_id = thing_id;
  return result;
}

static thing_id_list_t* dsda_ThingIDList(short thing_id) {
  thing_id_list_t* result;
  short index;

  index = thing_id % THING_ID_HASH_MAX;

  result = thing_id_list_hash[index];
  while (result && result->next && result->thing_id != thing_id)
    result = result->next;

  if (result) {
    if (result->thing_id != thing_id) {
      result->next = dsda_NewThingIDList(thing_id);
      result = result->next;
    }

    return result;
  }

  thing_id_list_hash[index] = dsda_NewThingIDList(thing_id);
  return thing_id_list_hash[index];
}

static thing_id_list_entry_t* dsda_NewThingIDListEntry(mobj_t* mo) {
  thing_id_list_entry_t* result;

  result = calloc(1, sizeof(*result));
  result->mo = mo;
  return result;
}

void dsda_AddMobjThingID(mobj_t* mo, short thing_id) {
  thing_id_list_t* list;

  list = dsda_ThingIDList(thing_id);

  // Note that there is no uniqueness check - this is consistent with hexen
  if (!list->last) {
    list->first = dsda_NewThingIDListEntry(mo);
    list->last = list->first;
  }
  else {
    list->last->next = dsda_NewThingIDListEntry(mo);
    list->last = list->last->next;
  }

  mo->tid = thing_id;
}

void dsda_RemoveMobjThingID(mobj_t* mo) {
  thing_id_list_t* list;
  thing_id_list_entry_t* entry;
  thing_id_list_entry_t* next;

  list = dsda_ThingIDList(mo->tid);

  if (list->first && list->first->mo == mo) {
    next = list->first->next;
    free(list->first);
    list->first = next;
  }
  else {
    for (entry = list->first; entry; entry = entry->next)
      if (entry->next && entry->next->mo == mo) {
        next = entry->next->next;
        free(entry->next);
        entry->next = next;
      }
  }

  mo->tid = 0;
}

mobj_t* dsda_FindMobjFromThingID(short thing_id, thing_id_list_entry_t** start) {
  thing_id_list_entry_t* p;

  p = *start;

  if (p)
    p = p->next;
  else {
    thing_id_list_t* list = dsda_ThingIDList(thing_id);
    p = list->first;
  }

  if (p) {
    *start = p;
    return p->mo;
  }

  *start = NULL;
  return NULL;
}
