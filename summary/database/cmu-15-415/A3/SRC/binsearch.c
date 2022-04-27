#include "def.h"
#include "defn.g"

/* seaches the given array for the given word
   'n' is the dimension of the array
   Returns the position of the located element or ERROR
 */

int binsearch(char *word, char **array, int n) {
    int low, high, mid;
    int res;

    assert(n > 0);
    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if ((res = strcmp(word, array[mid])) < 0)
            high = mid - 1;
        else if (res > 0)
            low = mid + 1;
        else
            return (mid);
    }
    return (ERROR);
}
