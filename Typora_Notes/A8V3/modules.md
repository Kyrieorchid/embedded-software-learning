# 通信协议

## UART

### 1. 简介
    1.1 半双工异步通信，


# BASIC

## PORT

### 1. XX
    1.1 PinMux配置的方向为in/out时，不支持“Port_Drv_SetPinMode”接口改mode，只能“Port_Drv_SetPinAllCfg”重新配置（方向可以用接口改）。
    1.2 


## ADC

### 1. XX
    1.1 ADC0 ~ ADC5 6个硬件单元，除ADC0外每单元8个通道channel0 ~ channel7，ADC0有额外的channel8可采样内部温度计。
    1.2 每个通道可单独设置优先级，优先级分4级。
    1.3 同一个硬件单元下的不同通道支持级联触发。
    1.4 采样频率不超过60MHz，故分频系数不小于3。

# 定时器

