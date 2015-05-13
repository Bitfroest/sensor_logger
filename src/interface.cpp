#include <sensor_logger.h>

extern "C" {
void* getInstance () {
    return new SensorLogger();
}
}
