#include "mbed.h"

Serial pc(USBTX, USBRX);

void log_on_terminal(const char* msg)
{
    pc.printf(msg);
       
}