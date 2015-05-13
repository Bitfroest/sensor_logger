#include "lms/module.h"
#include "lms/type/module_config.h"
#include "sense_board.h"
#include <gamepad/gamepad.h>

#include <iostream>
#include <fstream>

class SensorLogger : public lms::Module {
public:
    bool initialize() override;
    bool cycle() override;
    bool deinitialize() override;
private:
    const sense_link::SenseBoard *senseBoard;
    const Gamepad *gamePad;
    std::string savePath;
    std::vector<int> sensors;
    const lms::type::ModuleConfig* config;
    std::ofstream sensorlog;
};
