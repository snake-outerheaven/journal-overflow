#include "map.h"
#include <stdio.h>
#include <string.h>

int
main (void)
{
  char buffer[MAXBUF];
  map_t *my_map = map_init ();
  if (!my_map)
    {
      fprintf (stderr, "Error: Could not initialize inventory system.\n");
      return 1;
    }

  printf ("--- Grocery Inventory System ---\n");
  printf ("Adding items to stock...\n");

  map_insert (my_map, "001", "MILK:4.50");
  map_insert (my_map, "002", "BREAD:1.20");
  map_insert (my_map, "042", "COFFEE:12.80");
  map_insert (my_map, "099", "CHEESE:22.00");

  printf ("\nCurrent Stock:\n");
  map_print (my_map);
  printf ("Total items registered: %zu\n", map_size (my_map));

  printf ("\nSearching for item SKU 042...\n");
  if (map_get (my_map, "042", buffer) == 0)
    printf ("Found: %s\n", buffer);

  printf ("\nUpdating price for SKU 002 (BREAD)...\n");
  map_insert (my_map, "002", "BREAD:1.50");

  printf ("Checking if SKU 099 exists in database: ");
  if (map_contains (my_map, "099") == 0)
    printf ("Yes\n");
  else
    printf ("No\n");

  printf ("\nRemoving SKU 001 (MILK) from stock...\n");
  if (map_remove (my_map, "001") == 0)
    printf ("Item removed successfully.\n");

  printf ("\n--- Final Inventory Report ---\n");
  map_print (my_map);
  printf ("Total items: %zu\n", map_size (my_map));

  printf ("\nClosing system...\n");
  if (map_kill (&my_map) == 0)
    {
      printf ("Resources cleared.\n");
    }
  else
    {
      printf ("Error during cleanup.\n");
      return 1;
    }

  return 0;
}