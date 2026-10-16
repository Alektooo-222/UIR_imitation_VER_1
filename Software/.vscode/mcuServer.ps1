param([int] $cpu_frequency = 72000000)
Stop-Process -Name openocd -ErrorAction SilentlyContinue
#openocd `
#-f C:/OpenOCD-20250710-0.12.0/share/openocd/scripts/interface/stlink.cfg `
#-f C:/OpenOCD-20250710-0.12.0/share/openocd/scripts/target/stm32f3x.cfg `
##-c 'reset_config srst_only srst_nogate connect_assert_srst' `
##-c 'set CONNECT_UNDER_RESET 1' `
#-c 'gdb port 2000' `
#-c 'tcl port 2001' `
#-c 'telnet_port 2002' `
#-c 'adapter speed 1000' `
#-c 'bindto 0.0.0.0' `
#-c "tpiu config internal - uart off ${cpu_frequency}" `
#-c 'itm ports on'


openocd `
-f C:/OpenOCD-20250710-0.12.0/share/openocd/scripts/interface/stlink.cfg `
-f C:/OpenOCD-20250710-0.12.0/share/openocd/scripts/target/stm32f3x.cfg `
-c "transport select swd" `
-c "adapter speed 2000" `
-c "gdb port 2000" `
-c "tcl port 2001" `
-c "telnet port 2002" `
-c "bindto 0.0.0.0" `
-c "tpiu config internal - uart off 72000000" `
-c "itm ports on"