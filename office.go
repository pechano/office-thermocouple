package main

import (
    "machine"
    "time"
 "drivers/thermistor"
)

func main() {
    //Setup-delen
    led := machine.LED
    led.Configure(machine.PinConfig{Mode: machine.PinOutput})

    led2 := machine.PB2
    led.Configure(machine.PinConfig{Mode: machine.PinOutput})
/*
    thermoPin := machine.ADC0
    inputDevice :=thermistor.New(thermoPin)
    inputDevice.Configure()
    tempC,err := inputDevice.ReadTemperature()*/
    tempC := machine.ReadTemperature()
   // println(tempC)
   // if err != nil {println("an error has occrued")}  
   
    for {//uendelig loop
        led2.Low()
        time.Sleep(time.Millisecond * 1000)
 println("test")//terminal monitor på port /dev/ttyACM0 med 9600 baud rate kan faktisk læse den ehr.
        led2.High()
        time.Sleep(time.Millisecond * 1000)






    }
}


