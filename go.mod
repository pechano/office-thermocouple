module pechano/office-thermocouple

go 1.19

require device/avr v0.0.0 //indirect
require machine v0.0.0
require runtime/volatile v0.0.0 //indirect
require runtime/interrupt v0.0.0 //indirect
require device v0.0.0 //indirect

replace (
    device => /usr/lib/tinygo/src/device
    device/avr => /usr/lib/tinygo/src/device/avr
    internal/reflectlite => /usr/lib/tinygo/src/internal/reflectlite
    internal/task => /usr/lib/tinygo/src/internal/task
    machine => /usr/lib/tinygo/src/machine
    os => /usr/lib/tinygo/src/os
    reflect => /usr/lib/tinygo/src/reflect
    runtime => /usr/lib/tinygo/src/runtime
    runtime/interrupt => /usr/lib/tinygo/src/runtime/interrupt
    runtime/volatile => /usr/lib/tinygo/src/runtime/volatile
    sync => /usr/lib/tinygo/src/sync
    testing => /usr/lib/tinygo/src/testing
)
