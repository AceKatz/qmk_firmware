
# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina


CONSOLE_ENABLE     = yes  # Console for debug
MOUSEKEY_ENABLE    = no   # Mouse keys
THUMBSTICK_ENABLE  = yes  # Enables analog thumbstick code

# ifeq ($(strip $(THUMBSTICK_ENABLE)), yes)
POINTING_DEVICE_ENABLE = yes
OPT_DEFS += -DTHUMBSTICK_ENABLE
SRC += analog.c
SRC += thumbstick.c
# endif
