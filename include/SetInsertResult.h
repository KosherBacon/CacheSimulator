//
// Created by Joshua Kahn on 1/9/17.
//

#ifndef CACHESIMULATOR_SETINSERTRESULT_H
#define CACHESIMULATOR_SETINSERTRESULT_H

namespace Cache {
    typedef struct SetInsertResult {
        bool couldInsert;
        unsigned int lineNum;
    } SetInsertResult;
}

#endif //CACHESIMULATOR_SETINSERTRESULT_H
