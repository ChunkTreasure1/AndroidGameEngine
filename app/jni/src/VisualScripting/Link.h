//
// Created by chunktreasure on 8/2/21.
//

#ifndef TESTPROJECT_LINK_H
#define TESTPROJECT_LINK_H

struct InputAttribute;
struct OutputAttribute;

struct Link
{
    InputAttribute* pInput = nullptr;
    OutputAttribute* pOutput = nullptr;

    uint32_t id;
};

#endif //TESTPROJECT_LINK_H
