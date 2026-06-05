//
// Created by xac1k on 4/27/26.
//

#ifndef MAIN_CONTEXT_H
#define MAIN_CONTEXT_H

struct IContext {
    virtual ~IContext () = default;
};

inline IContext EMPTY_CTX;

#endif //MAIN_CONTEXT_H