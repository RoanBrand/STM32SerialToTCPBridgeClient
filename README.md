# STM32 Serial To TCP Bridge Client
STM32 based client for [SerialToTCPBridgeProtocol](https://github.com/RoanBrand/SerialToTCPBridgeProtocol) gateway service.

Open a TCP connection to a server from the STM32 using just UART. (No shields or network HW)  
See [this](https://github.com/RoanBrand/SerialToTCPBridgeProtocol) for more information on the protocol and for the **Protocol Gateway** you will need to run on the host the STM32 is connected to serially.  
Currently, there is a MQTT protocol implementation over this connection as an example.

## Used
- Atollic TrueSTUDIO for ARM Lite 5.5.2+
- STM32CubeMX plugin for Eclipse (4.15.1.201606091139)
- STM32F3 firmware package (1.5.0)
- STM32 Nucleo F334R8 board

## How to
- Install software.
- Clone repo in your Atollic workspace.
- Open Atollic by clicking `.project` file.
- In Atollic, open the STM32CubeMX perspective.
- Inside STM32CubeMX, open `STM32SerialToTCPBridgeClient.ioc` file. Click *Generate source code*.
- In Atollic, open C/C++ perspective and click *Rebuild*.
- Get the [Protocol Gateway](https://github.com/RoanBrand/SerialToTCPBridgeProtocol) and build it.
- Change the gateway's config to listen on the COM port connected to your STM32 and start it.
- With the STM32 Nucleo ST-Link debugger connected, click *Debug* to load the program.
- Once in the Debug perspective, click *Resume* to start program on STM32.

#### Details
- The protocol provides the app an in order, duplicates free and error checked byte stream by adding a CRC32 and simple retry mechanism. See [this](https://en.wikibooks.org/wiki/Serial_Programming/Error_Correction_Methods) for background.
- The Protocol utilizes the internal CRC32 unit on the STM32 for communication error checking.
- The **Protocol Gateway** opens a real TCP connection to a set destination on behalf of the **Protocol Client** running on the STM32, and forwards traffic bi-directionally.

#### Included Example
- A stripped down version of [knolleary's MQTT library for Arduino](https://github.com/knolleary/pubsubclient) is used.
- When the microcontroller starts up it dials to a HiveMQ MQTT broker running on the host. (127.0.0.1, 1883)
- Pressing the button on the Nucleo board the first time causes it to subscribe to topic `led/#`. Subsequent presses publishes a message on another MQTT topic.
- Publishing `1` from another MQTT client to the `led` topic will power on the led on the Nucleo board. Publishing `2` will power it off.

#### Future plans
- Optimization & more protocol feature complete
- Unit tests
