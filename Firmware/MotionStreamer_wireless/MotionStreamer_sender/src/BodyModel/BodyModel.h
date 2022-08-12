#include "IMUsensors/TinyBMX160.h"
#include "IMUsensors/Adafruit_FXOS8700.h"
#include "IMUsensors/Adafruit_FXAS21002C.h"
#include "OrientationAlgorithm/MadgwickAHRS.h"





// struct for holding IMU data
struct IMUdata{
    float gyro[3];
    float acc[3];
    float quat[4] = {1, 0, 0, 0};
};





class BodyModel{
private:
    // IMU for right thigh
    TinyBMX160 rightIMU;

    // IMU for left thigh
    TinyBMX160 leftIMU;

    // IMU for waist
    Adafruit_FXOS8700 waistAccelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);
    Adafruit_FXAS21002C waistGyro = Adafruit_FXAS21002C(0x0021002C);

    // AHRS filters
    Madgwick rightFilter;
    Madgwick leftFilter;
    Madgwick waistFilter;

    // initialise BMX160 IMU
    void beginBMX160(TinyBMX160* IMU, uint8_t addr);

    // initialise FXOS8700 Accelerometer/Magnetometer
    void beginNPX(Adafruit_FXOS8700* accelmag, Adafruit_FXAS21002C* gyro);



    // get IMU data
    void getDataBMX160(TinyBMX160* IMU, float* data);
    
    void getDataNPX(Adafruit_FXOS8700* accelmag, Adafruit_FXAS21002C* gyro, float* data);

    void gatherIMUdata(struct IMUdata* dst, float* data, Madgwick* filter);



public:
    // IMU data holder
    struct IMUdata right;
    struct IMUdata left;
    struct IMUdata waist;

    BodyModel();

    void begin(float freq);

    void filter();

    void getFlattenedData(float* data);
};