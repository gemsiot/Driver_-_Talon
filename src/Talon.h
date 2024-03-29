//© 2023 Regents of the University of Minnesota. All rights reserved.

#ifndef Talon_h
#define Talon_h

#include <Sensor.h>

class Talon: public Sensor
{
	public:
		// Talon();
		virtual String begin(time_t time, bool &criticalFault, bool &fault);
		virtual int restart() {
			return -1; //DEBUG!
		};
		virtual bool hasReset();
		virtual int enableData(uint8_t Port, bool state){
			return 0;
		};
		virtual int enablePower(uint8_t Port, bool state){
			return 0;
		};
		int disableDataAll(){
			for(int i = 1; i <= 4; i++) {
				enableData(i, false);
			}
			return 0;
		};
		int disablePowerAll(){
			for(int i = 1; i <= 4; i++) {
				enablePower(i, false);
			}
			return 0;
		};
		// uint8_t getPort() {
		// 	if(talonPort < 255) return talonPort + 1;
		// 	else return 0;
		// }
		// void setPort(uint8_t port)
		// {
		// 	// // if(port_ > numPorts || port_ == 0) throwError(PORT_RANGE_ERROR | portErrorCode); //If commanded value is out of range, throw error 
		// 	// if(port > 4 || port == 0) throwError(TALON_PORT_RANGE_ERROR | talonPortErrorCode | sensorPortErrorCode); //If commanded value is out of range, throw error //FIX! How to deal with magic number? This is the number of ports on KESTREL, how do we know that??
		// 	// else { //If in range, update the port values
		// 	// 	talonPort = port - 1; //Set global port value in index counting
		// 	// 	talonPortErrorCode = (talonPort + 1) << 4; //Set port error code in rational counting 
		// 	// }
			
		// }
		// // virtual void setPort(uint8_t port_);
		// virtual bool isPresent();
	// protected:
		virtual uint8_t getNumPorts() {
			return 0; //DEBUG!
		};
		uint8_t talonInterface = 0;
		bool keepPowered = false; ///<Set if there is a sensor on the Talon which should stay powered
	protected:
		const uint32_t TALON_MISSING = 0xEF000000;
		const uint32_t CSA_READ_FAIL = 0x10130000; ///<Attempt for Talon to read CSA for power test but fail
		const uint32_t SENSOR_POWER_INIT_FAIL = 0x20040000; ///<Power to a sensor port failed to initialize 
		const uint32_t TALON_POWER_FAIL_EXCESS = 0x20060000; ///<Power to the Talon exceeded max during the init process
		const uint32_t SENSOR_POWER_FAIL = 0x20010000; //(low 2 bits are which port)
		const uint32_t SENSOR_POWER_FAIL_PERSISTENT = 0x20010100; //(low 2 bits are which port)
		const uint32_t SENSOR_POWER_WARNING = 0xF0170000; //(low 2 bits are which port) (1 = Exceed on rising)
		const uint32_t TALON_EEPROM_READ_FAIL = 0x10090000; ///<Report failure to read from Talon EEPROM 
		const uint32_t SENSE_ADC_INIT_FAIL = 0x10060000; ///<Error in initalizing the port sense ADC (MCP3421)
		const uint32_t SENSOR_PORT_RANGE_ERROR = 0x90010100; 
		const uint32_t IO_INIT_FAIL = 0x100F0000; ///<Failure to initialize IO expander, port coresponds to which IO expander (1 = Alpha, 2 = Beta, 3 = Gamma)
		const uint32_t PORT_ADC_INIT_FAIL = 0x10070000; ///<Failure to initialize port reading ADC (MCP3221) 
		// const uint32_t TALON_PORT_RANGE_ERROR = 0x90010200; //FIX! 
		// uint8_t sensorInterface = BusType::NONE;
		// uint8_t talonPort = 255; //Used to keep track of which port the Talon is connected to on Kestrel
		// uint8_t sensorPort = 255; //Used to keep track of which port the sensor is connected to on associated Talon
		// virtual uint8_t getPort();
		// virtual void setPort(uint8_t port);

};

#endif