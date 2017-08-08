#ifndef HX711_H_
#define HX711_H_
    
	
		
		void hx711_init(void);
		
		// check if HX711 is ready
		// from the datasheet: When output data is not ready for retrieval, digital output pin DOUT is high. Serial clock
		// input PD_SCK should be low. When DOUT goes to low, it indicates data is ready for retrieval.
		int is_ready(void);

		// set the gain factor; takes effect only after a call to read()
		// channel A can be set for a 128 or 64 gain; channel B has a fixed 32 gain
		// depending on the parameter, the channel is also set to either A or B
		void set_gain(int gain );

		// waits for the chip to be ready and returns a reading
		unsigned long read(void);
		
		#endif
		

