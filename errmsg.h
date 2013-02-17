#ifndef ERRMSG_H 
#define ERRMSG_H 
#define P(E) std::cout << #E "=" << E << std::endl

#define ERR_NO_ERROR	0                       /* No error */
#define ERR_OPEN_FILE	1                       /* Open file error */
#define ERR_GRAB_FRAME	2                       /* Grab frame error */
#define ERR_ARGUMENT	3                       /* argument error */

void perrmsg(const char* info);

#endif //ERRMSG_H
