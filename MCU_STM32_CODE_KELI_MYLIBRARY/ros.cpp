#include "ros.h"

namespace ros {
    void normalizeSecNSec ( unsigned& sec, unsigned& nsec ) {
        while ( nsec >= 1000000000 ) {
            nsec -= 1000000000;
            ++sec;
        }
    }
}
