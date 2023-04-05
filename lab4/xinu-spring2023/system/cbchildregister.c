/* cbchildregister.c - cbchildregister */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  cbchildregister - register a callback function for a new processz
 *------------------------------------------------------------------------
 */
extern syscall cbchildregister(void (*cbf)(void)) {
    return 0;
}