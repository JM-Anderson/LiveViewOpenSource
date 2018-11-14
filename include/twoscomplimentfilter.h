#ifndef TWOSCOMPLIMENTFILTER_H
#define TWOSCOMPLIMENTFILTER_H

#include <stdint.h>
#include <QDebug>

#include "constants.h"
#include "image_type.h"

class TwosComplimentFilter
{
public:
    explicit TwosComplimentFilter(unsigned int frame_height, unsigned int frame_width);
    void apply_filter(uint16_t *pic_in, bool is16bit);

private:
    uint16_t pic_buffer[MAX_SIZE];
    unsigned int frHeight;
    unsigned int frWidth;
};

#endif // TWOSCOMPLIMENTFILTER_H
