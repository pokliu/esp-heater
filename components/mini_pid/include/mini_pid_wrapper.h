#include "mini_pid.hpp"

#ifdef __cplusplus
extern "C" {
#endif

void* MiniPIDInit(double, double, double);
void* MiniPIDInitF(double, double, double, double);
void MiniPIDsetP(void* pid, double);
void MiniPIDsetI(void* pid, double);
void MiniPIDsetD(void* pid, double);
void MiniPIDsetF(void* pid, double);
void MiniPIDsetPID(void* pid, double, double, double);
void MiniPIDsetPIDF(void* pid, double, double, double, double);
void MiniPIDsetMaxIOutput(void* pid, double output);
void MiniPIDsetOutputLimits(void* pid, double);
void MiniPIDsetOutputLimitsF(void* pid, double,double);
void MiniPIDsetDirection(void* pid, bool);
void MiniPIDsetSetpoint(void* pid, double);
void MiniPIDreset(void* pid);
void MiniPIDsetOutputRampRate(void* pid, double);
void MiniPIDsetSetpointRange(void* pid, double);
void MiniPIDsetOutputFilter(void* pid, double);
double MiniPIDgetOutput(void* pid);
double MiniPIDgetOutputA(void* pid, double);
double MiniPIDgetOutputAS(void* pid, double, double);

#ifdef __cplusplus
}
#endif