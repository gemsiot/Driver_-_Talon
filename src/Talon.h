#ifndef Talon_h
#define Talon_h

#include <Sensor.h>

class Talon: public Sensor
{
	public:
		// Talon(uint8_t port);
		// static bool isPresent();
		// static constexpr const char* CLASS_NAME;
		virtual String begin(time_t time, bool &criticalFault, bool &fault) = 0;
		virtual int restart() = 0;
		virtual bool hasReset() = 0;
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
	// protected:
		virtual uint8_t getNumPorts() {
			return 0; //DEBUG!
		};
		uint8_t talonInterface = 0;
		bool keepPowered = false; ///<Set if there is a sensor on the Talon which should stay powered
	protected:
		// const uint32_t TALON_PORT_RANGE_ERROR = 0x90010200; //FIX! 
		// uint8_t sensorInterface = BusType::NONE;
		// uint8_t talonPort = 255; //Used to keep track of which port the Talon is connected to on Kestrel
		// uint8_t sensorPort = 255; //Used to keep track of which port the sensor is connected to on associated Talon
		// virtual uint8_t getPort();
		// virtual void setPort(uint8_t port);

};

struct TalonFactory {
	bool (*isPresent)();
	Talon* (*create)(uint8_t port);
	const char* name;

	template <typename TalonType>
	static Talon* CreateTalon(uint8_t port) {
		// If you see errors here, your talon is lacking a constructor accepting (uint8_t port)
		return new TalonType(port);
	}
	template <typename TalonType>
	static constexpr TalonFactory Create() {
		// If you see errors here, your talon is lacking an isPresent(uint8_t port)
		bool (*isPresent)() = TalonType::isPresent;
		// If you see errors here, your talon is lacking a constexpr static const char* CLASS_NAME;
		const char* name = TalonType::CLASS_NAME;
		Talon* (*create)(uint8_t port) = CreateTalon<TalonType>;
		return {isPresent, create, name};
	}
};

#endif
