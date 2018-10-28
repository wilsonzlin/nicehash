#pragma once

#include <stdint.h>
#include <string.h>
#include "./list.h"
#include "./list-char.h"

NH_LIST(nh_list_list_char, nh_list_char_t, sizeof(nh_list_char_t), nh_list_char_t, NULL);

int nh_list_list_char_compare(nh_list_list_char_t a, nh_list_list_char_t b)
{
  size_t max = a->length > b->length ? a->length : b->length;

  for (size_t i = 0; i < max; i++)
  {
    nh_list_char_t a1 = nh_list_list_char_get(a, i);
    nh_list_char_t b1 = nh_list_list_char_get(b, i);

    if (a1 == NULL)
    {
      return -1;
    }

    if (b1 == NULL)
    {
      return 1;
    }

    int subcmp = nh_list_char_compare(a1, b1);
    if (subcmp != 0)
    {
      return subcmp;
    }
  }

  return 0;
}

nh_list_list_char_t nh_list_list_char_create_from_split(char* source, char delim)
{
  nh_list_list_char_t parts = nh_list_list_char_create();
  nh_list_char_t part = nh_list_char_create();
  nh_list_list_char_append(parts, part);

  hb_char_t c;
  size_t i = 0;
  while ((c = source[i]))
  {
    if (c == delim)
    {
      part = nh_list_char_create();
      nh_list_list_char_append(parts, part);
    }
    else
    {
      nh_list_char_append(part, c);
    }

    i++;
  }

  return parts;
}

void nh_list_list_char_destroy_from_split(nh_list_list_char_t list)
{
  for (size_t i = 0; i < list->length; i++) {
    nh_list_char_destroy(nh_list_list_char_get(list, i));
  }
  nh_list_list_char_destroy(list);
}
