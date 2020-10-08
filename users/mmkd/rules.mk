# RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
BOOTMAGIC_ENABLE = no      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = no      # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no           # USB Nkey Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality on B7 by default
# OLED_DRIVER_ENABLE=yes

AUDIO_ENABLE = no          # Audio output on port C6
AUTOLOG_ENABLE = no
BLUETOOTH_ENABLE = no      # Enable Bluetooth with the Adafruit EZ-Key HID
DEBUG_ENABLE = no
FAUXCLICKY_ENABLE = no     # Use buzzer to emulate clicky switches
HD44780_ENABLE = no        # Enable support for HD44780 based LCDs
LEADER_ENABLE = no
MIDI_ENABLE = no           # MIDI support
SLEEP_LED_ENABLE = yes
SPACE_CADET_ENABLE = no             # Unneeded feature.
# TAP_DANCE_ENABLE = no
UCIS_ENABLE = no


SRC += mmkd.c

ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
    SRC += animations.c\
     			 oled_stuff.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    SRC += rgb_underglow.c
endif
