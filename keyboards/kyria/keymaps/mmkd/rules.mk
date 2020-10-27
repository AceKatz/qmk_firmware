# USER_NAME := mmkd

# OLED_DRIVER_ENABLE = yes   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
# RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
WPM_ENABLE = yes

# BOOTMAGIC_ENABLE = no      # Virtual DIP swit
SPLIT_KEYBOARD = yes
EXTRAFLAGS += -flto
# src += printf.c
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina
