# STM32 LED Control with UART Interface

## Hardware Used

- Board: **STM32 Nucleo-F446ZE**
- LED: **LD1 (PB0)**
- Button: **B1 (PC13, EXTI interrupt)**
- UART: **USART3**
  - TX: PD8  
  - RX: PD9  
  - Baud rate: 115200
- Connection: ST-Link USB (Virtual COM Port)

---

## Build / Flash Steps

1. Open the project in **STM32CubeIDE**.
2. Build the firmware:  
   `Project → Build Project`  
   or press `Ctrl + B`.
3. Connect the Nucleo board via the **ST-Link USB**.
4. Flash the firmware:  
   `Run → Run`  
   or press `Ctrl + F11`.

---

## UART Usage

Serial settings:

- Baud rate: **115200**
- Data bits: **8**
- Parity: **None**
- Stop bits: **1**
- Line ending: **CRLF**

Supported commands:

### status  
Returns current mode and blink period.

Example:

```
> status
< OK mode=BLINK period=500
```

### period <ms>  
Sets blink period in milliseconds.

Example:

```
> period 250
< OK mode=BLINK period=250
```

Invalid commands return:

```
ERR unknown command
ERR invalid argument
```

Button press toggles:

```
BLINK ↔ SOLID
```

---

## Code Structure

```
Core/
 ├── Inc/
 │    led.h         LED control interface
 │    button.h      Button interrupt handling
 │    uart_cmd.h    UART command interface
 │    app.h         Application logic
 │    main.h        Common app defines
 ├── Src/
 │    led.c         LED mode + timing logic
 │    button.c      EXTI button handling
 │    uart_cmd.c    UART command parsing
 │    app.c         Mode switching logic
 │    main.c        System initialization and loop
```
