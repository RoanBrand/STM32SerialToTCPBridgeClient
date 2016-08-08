/*
 * SerialToTCPBridgeProtocol.h
 *
 *  Created on: Jul 29, 2016
 *      Author: Roan
 */

#ifndef SERIALTOTCPBRIDGEPROTOCOL_H_
#define SERIALTOTCPBRIDGEPROTOCOL_H_

#include <stdbool.h>
#include "stm32f3xx_hal.h"

#define SERIAL_TIMEOUT 400

// Protocol Packet Headers
#define PROTOCOL_CONNECT 0
#define PROTOCOL_CONNACK 1
#define PROTOCOL_DISCONNECT 2
#define PROTOCOL_PUBLISH 3
#define PROTOCOL_ACK 4

// Protocol Link State
#define STATE_DISCONNECTED 0
#define STATE_CONNECTED 1

// Protocol Packet RX State
#define RX_PACKET_IDLE 0
#define RX_PACKET_GOTLENGTH 1
#define RX_PACKET_GOTCOMMAND 2

// "class"
typedef struct Client_t
{
	UART_HandleTypeDef* peripheral_UART;
	CRC_HandleTypeDef* peripheral_CRC;

	// Buffer for incoming uart data
	uint8_t rxByte;
	uint8_t rxBuffer[256];

	// Buffer for outgoing uart data
	uint8_t txBuffer[256];
	uint8_t pHead_tx;
	uint8_t pTail_tx;
	bool txFull;

	// buffer for app data to be read
	uint8_t readBuffer[256];
	uint8_t pRx_read, pRead_read;
	bool readFull;

	uint8_t workBuffer[128];
	bool txReady;
	bool ackOutstanding;
	bool sequenceTxFlag;
	bool expectedRxSeqFlag;
	uint32_t lastInAct, lastOutAct;
	uint8_t state;

	// Arduino Client interface API
	int (*connect)(const void*, uint8_t ip[4], uint16_t port);
	uint8_t (*connected)(const void*);
	int (*available)(const void*);
	int (*read)(const void*);
	size_t (*write)(const void*, uint8_t* payload, uint8_t pLength);
	void (*flush)(const void*); // wait until all sent
	void (*stop)(const void*);
} Client;

// Constructor
void newClient(Client*, UART_HandleTypeDef* uartUnit, CRC_HandleTypeDef* crcUnit);

// Callback hook ups
void uartTxCompleteCallback(Client* c);
void uartRxCompleteCallback(Client* c);

#endif /* SERIALTOTCPBRIDGEPROTOCOL_H_ */
