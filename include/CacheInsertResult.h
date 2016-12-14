//
// Created by Joshua Kahn on 12/14/16.
//

#ifndef CACHESIMULATOR_INSERTRESULT_H
#define CACHESIMULATOR_INSERTRESULT_H

namespace Cache {
    typedef struct CacheInsertResult {
        bool couldInsert;
        unsigned int setNum;
        unsigned int lineNum;
    } CacheInsertResult;
}

#endif //CACHESIMULATOR_INSERTRESULT_H
