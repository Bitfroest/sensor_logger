#include "sensor_logger.h"
#include "lms/datamanager.h"
#include "gamepad/gamepad.h"
#include <lms/extra/time.h>

#include <cmath>

#include <iostream>
#include <fstream>

bool SensorLogger::initialize(){
    config = getConfig();
    savePath = config->get<int>("savePath");
    sensors = config->getArray<int>("sensors");

    senseBoard = datamanager()
            ->readChannel<sense_link::SenseBoard>(this, "SENSE_BOARD");
    gamePad = datamanager()
            ->readChannel<Gamepad>(this,"360");

    sensorlog.open ("servolog.csv");
    sensorlog << "Time;";
    for(int i = 0;i< sensors.size();i++){
        sensorlog << sensors[i] << ";";
    }
    sensorlog << "\n";
    return true;
}

bool SensorLogger::cycle(){
    using sense_link::SensorData;

    SensorData data;
    sensorlog << lms::extra::PrecisionTime::now() << ";";
    for(int i = 0; i < sensors.size(); i++){
        if(senseBoard->getSensor((sense_link::SensorType) sensors[i],1,data)){
            if(sensors[i] == sense_link::SensorType::MOTOR_VELOCITY){
                sensorlog << data.MotorVelocity.acceleration << ";";
            }else if(sensors[i] == sense_link::SensorType::SERVO){
                sensorlog << data.Servo.angle << ";";
            }else{
                sensorlog << sensors[i] << ";";
            }
        }else {
            sensorlog << ";";
        }
    }
    sensorlog << "\n";
    return true;
}

bool SensorLogger::deinitialize(){
    sensorlog.close();
    return true;
}
