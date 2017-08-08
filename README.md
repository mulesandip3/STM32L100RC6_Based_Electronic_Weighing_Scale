
# STM32L100RC6_Based_Electronic_Weighing_Scale

Hardware USED
1) STM32L1 Series Discovery Board 
2)HX711 24 Bit ADC
3)Sparkfun Combinator Circuit
4)LCD 16x2
5)4 Ouarter Brigde 3 wire load cell 

step 1)
form a bridge of of 4 load cell refer sparkfun combinator pdf.
step2)
connect combinator output pin to i.e E+ , E- , A+ and A- to HX711 ADC ckt ref sparkfun HX711 .
Step 3)
With help of single wire communication interface hx711 24 bit adc to STM32L100RC6 MCU .
step4)
read adc count .
step 5)
convet count into weight .
step 6) 
display on lcd ,uart etc
step 7).
done.

