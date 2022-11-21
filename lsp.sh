#!/bin/bash

export GOOS=linux
export GOARCH=arm
export GOFLAGS=-tags=avr,baremetal,linux,arm,atmega328p,atmega,avr5,arduino,tinygo,math_big_pure_go,gc.conservative,scheduler.none,serial.uart
nvim .
