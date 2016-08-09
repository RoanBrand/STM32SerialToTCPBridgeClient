# STM32 Serial To TCP Bridge Client
STM32 based client for [SerialToTCPBridgeProtocol](https://github.com/RoanBrand/SerialToTCPBridgeProtocol) PC side service.

Currently, there is a MQTT protocol implementation over this connection as an example.
The microcontroller is effectively making a connection to a MQTT broker over the virtual COM USB.

## Used
- Atollic TrueSTUDIO for ARM Lite 5.5.2
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
- With the STM32 Nucleo connected, click *Debug* then *Resume*, once in the Debug perspective.

#### Details
- The Go service opens a real TCP connection to a set destination on behalf of the STM32 Serial Client.
- The Protocol utilizes the internal CRC32 unit on the STM32 for communication error checking.
- A stripped down version of [knolleary's MQTT library for Arduino](https://github.com/knolleary/pubsubclient) is used.
- When the microcontroller starts up it dials to a HiveMQ MQTT broker running on the host PC (127.0.0.1, 1883)
- Pressing the button on the Nucleo board the first time causes it to subscribe to topic `led/#`. Subsequent presses publishes a message on another MQTT topic.
- Publishing `1` from another MQTT client to the `led` topic will power on the led on the Nucleo board. Publishing `2` will power it off.

#### Future plans
- Sort out timeout bugs
- Unit tests
- Create a Arduino lib/client that extends the [Arduino Client class](https://www.arduino.cc/en/Reference/ClientConstructor) so that libraries for existing Ethernet/Wifi shields can theoretically work.
