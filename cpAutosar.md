# 经典AUTOSAR软件架构

## 1. 应用层（Application Layer）
应用层是AUTOSAR架构的最高层，负责实现具体的功能（如ADAS、车身控制等）。这些功能通过**软件组件（SWC, Software Component）**实现，SWC之间通过**端口（Port）**进行交互。

### 1.1 SWC与端口交互示例：驾驶辅助功能
驾驶辅助功能可以分解为以下SWC：
1. **传感器数据采集组件（SensorDataAcquisition）**
   - 负责从雷达、摄像头等传感器获取原始数据。
   - 提供 **Sender Port**，输出传感器数据（如距离、速度、图像帧）。

2. **数据处理组件（DataProcessing）**
   - 接收传感器数据，进行滤波、融合等处理。
   - 提供 **Receiver Port** 接收传感器数据，提供 **Sender Port** 输出处理后的数据。

3. **决策组件（DecisionMaking）**
   - 根据处理后的数据判断是否需要刹车、转向等操作。
   - 提供 **Receiver Port** 接收处理后的数据，提供 **Sender Port** 输出决策结果。

4. **执行组件（ActuatorControl）**
   - 根据决策结果控制刹车、转向等执行器。
   - 提供 **Receiver Port** 接收决策结果。

### 1.2 端口交互
- **SensorDataAcquisition** 通过 **Sender Port** 发送数据到 **DataProcessing** 的 **Receiver Port**。
- **DataProcessing** 通过 **Sender Port** 发送处理后的数据到 **DecisionMaking** 的 **Receiver Port**。
- **DecisionMaking** 通过 **Sender Port** 发送决策结果到 **ActuatorControl** 的 **Receiver Port**。

### 1.3 组件复用
- **SensorDataAcquisition** 可以复用于其他功能（如自动泊车、车道保持）。
- **DataProcessing** 可以复用于其他需要数据处理的场景（如环境感知、目标跟踪）。
- **DecisionMaking** 可以根据不同场景调整算法，但接口（Port）保持不变。

---

## 2. 运行时环境（RTE, Runtime Environment）
RTE是应用层与底层（BSW）的桥梁，负责通信和交互。

### 2.1 RTE的核心功能
- 实现SWC之间的通信（同一ECU内或跨ECU）。
- 将SWC的通信抽象映射到底层通信协议（如CAN、LIN、Ethernet）。
- 依赖BSW的通信模块（如COM、PDU Router）实现实际的总线通信。

---

## 3. 基础软件层（BSW, Basic Software）
BSW为应用层提供标准化服务，分为三层：

### 3.1 服务层（Services Layer）
- 包括 **操作系统（OS）**、**通信协议栈（COM、CAN、LIN、FlexRay、Ethernet）**、**诊断服务（UDS、DTC）**、**存储管理（NvM）**、**网络管理（NM）** 等。
- **OS** 负责任务调度、中断管理、资源保护（符合OSEK/VDX标准）。

### 3.2 ECU抽象层（ECU Abstraction Layer）
- 提供硬件无关接口，如 **I/O控制（IoHwAb）**、**外设抽象（如SPI、ADC抽象）**。

### 3.3 微控制器抽象层（MCAL, Microcontroller Abstraction Layer）
- 直接驱动硬件外设（如GPIO、ADC、PWM、CAN控制器）。
- 与硬件紧密绑定，直接操作MCU寄存器。

---

## 4. 硬件层（Hardware Layer）
- 包括MCU、传感器、执行器等物理硬件。
- MCAL是硬件与BSW的桥梁，直接读写硬件寄存器。
- 可能包含 **复杂驱动（CDD, Complex Device Drivers）** 用于非标准外设（如摄像头、雷达）。

---

## 5. 常见问题与解答

### 5.1 OS属于BSW的服务层，运行在哪个上？
- **OS的运行位置**：  
  OS运行在 **微控制器（MCU）** 上，属于 **BSW服务层** 的一部分。  
  - OS直接管理MCU的硬件资源（如CPU、内存、中断）。  
  - OS通过 **MCAL（微控制器抽象层）** 访问硬件外设（如定时器、看门狗）。  

- **OS与硬件的关系**：  
  - OS是软件，运行在MCU的硬件上。  
  - OS通过 **MCAL** 与硬件交互，MCAL是OS与硬件之间的桥梁。  

- **OS在AUTOSAR架构中的位置**：  
  - OS属于 **BSW服务层**，提供任务调度、中断管理、资源保护等功能。  
  - OS的配置通过 **AUTOSAR工具链** 完成（如Vector的Davinci Configurator）。  

---

## 6. 总结
- 经典AUTOSAR通过分层架构实现了 **硬件无关性** 和 **功能可复用性**。
- 应用层通过SWC和端口实现功能分解与交互。
- RTE是应用层与BSW的桥梁，负责通信调度。
- BSW分为服务层、ECU抽象层和MCAL，提供标准化服务。
- OS运行在MCU上，属于BSW服务层，负责任务调度和资源管理。