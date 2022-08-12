#include "BodyModel.h"




// setting up functions
BodyModel::BodyModel(){}

void BodyModel::begin(float freq){
    beginBMX160(&rightIMU, 0x68);
    beginBMX160(&leftIMU, 0x69);
    beginNPX(&waistAccelmag, &waistGyro);
    rightFilter.begin(freq);
    leftFilter.begin(freq);
    waistFilter.begin(freq);
}

void BodyModel::beginBMX160(TinyBMX160* IMU, uint8_t addr){
    IMU->begin(addr);
    IMU->setAccelRange(eAccelRange_16G);
}

void BodyModel::beginNPX(Adafruit_FXOS8700* accelmag, Adafruit_FXAS21002C* gyro){
    accelmag->begin();
    accelmag->setAccelRange(ACCEL_RANGE_8G);
    accelmag->setOutputDataRate(ODR_400HZ);
    gyro->begin();
    gyro->setRange(GYRO_RANGE_250DPS);
}





// get IMU data functions
void BodyModel::getDataBMX160(TinyBMX160* IMU, float* data){
    sBmx160SensorData_t mag, gyro, acc;
    IMU->getAllData(&mag, &gyro, &acc);
    data[0] = gyro.z * 8 * 0.0174533;
    data[1] = gyro.x * 8 * 0.0174533;
    data[2] = gyro.y * 8 * 0.0174533;
    data[3] = acc.z * 0.125;
    data[4] = acc.x * 0.125;
    data[5] = acc.y * 0.125;
    data[6] = mag.z;
    data[7] = mag.x;
    data[8] = mag.y;
}

void BodyModel::getDataNPX(Adafruit_FXOS8700* accelmag, Adafruit_FXAS21002C* gyro, float* data){
    sensors_event_t acc, mag;
    accelmag->getEvent(&acc, &mag);
    sensors_event_t gyr;
    gyro->getEvent(&gyr);
    data[0] = gyr.gyro.z*2;
    data[1] = gyr.gyro.x*2;
    data[2] = gyr.gyro.y*2;
    data[3] = acc.acceleration.z;
    data[4] = acc.acceleration.x;
    data[5] = acc.acceleration.y;
    data[6] = mag.magnetic.z;
    data[7] = mag.magnetic.x,
    data[8] = mag.magnetic.y;
}





// AHRS filtering
void BodyModel::gatherIMUdata(struct IMUdata* dst, float* data, Madgwick* filter){
    dst->gyro[0] = data[0];
    dst->gyro[1] = data[1];
    dst->gyro[2] = data[2];
    dst->acc[0] = data[3];
    dst->acc[1] = data[4];
    dst->acc[2] = data[5];
    dst->quat[0] = filter->q0;
    dst->quat[1] = filter->q1;
    dst->quat[2] = filter->q2;
    dst->quat[3] = filter->q3;
}

void BodyModel::filter(){
    float data[9];

    getDataBMX160(&rightIMU, data);
    rightFilter.updateIMU(data[0], data[1], data[2], data[3], data[4], data[5]);
    gatherIMUdata(&right, data, &rightFilter);

    getDataBMX160(&leftIMU, data);
    leftFilter.updateIMU(data[0], data[1], data[2], data[3], data[4], data[5]);
    gatherIMUdata(&left, data, &leftFilter);

    getDataNPX(&waistAccelmag, &waistGyro, data);
    waistFilter.updateIMU(data[0], data[1], data[2], data[3], data[4], data[5]);
    gatherIMUdata(&waist, data, &waistFilter);
    
}





// get data
void BodyModel::getFlattenedData(float* data){
    data[0] = waist.gyro[0];
    data[1] = waist.gyro[1];
    data[2] = waist.gyro[2];
    data[3] = waist.acc[0];
    data[4] = waist.acc[1];
    data[5] = waist.acc[2];
    data[6] = waist.quat[0];
    data[7] = waist.quat[1];
    data[8] = waist.quat[2];
    data[9] = waist.quat[3];
    data[10] = right.gyro[0];
    data[11] = right.gyro[1];
    data[12] = right.gyro[2];
    data[13] = right.acc[0];
    data[14] = right.acc[1];
    data[15] = right.acc[2];
    data[16] = right.quat[0];
    data[17] = right.quat[1];
    data[18] = right.quat[2];
    data[19] = right.quat[3];
    data[20] = left.gyro[0];
    data[21] = left.gyro[1];
    data[22] = left.gyro[2];
    data[23] = left.acc[0];
    data[24] = left.acc[1];
    data[25] = left.acc[2];
    data[26] = left.quat[0];
    data[27] = left.quat[1];
    data[28] = left.quat[2];
    data[29] = left.quat[3];
}