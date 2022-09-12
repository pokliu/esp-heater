#include "mini_pid_wrapper.h"
#include "esp_log.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TAG "MINIPID"

#define _MINIPID(x) static_cast<MiniPID*>(x)

void* MiniPIDInit(double p, double i, double d)
{
    return new MiniPID(p, i, d);
}

double MiniPIDgetOutputAS(void* pid, double actual, double setpoint)
{
    return _MINIPID(pid)->getOutput(actual, setpoint);
}


void MiniPIDsetMaxIOutput(void* pid, double output)
{
    return _MINIPID(pid)->setOutputLimits(output);
}

#ifdef __cplusplus
}
#endif