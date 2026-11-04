cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(final)

pico_sdk_init()

add_executable(final)

pico_generate_pio_header(final
    ${CMAKE_CURRENT_LIST_DIR}/SPIPIO.pio
)

target_sources(final PRIVATE
    ts_lcd.c
    TouchScreen.c
    TFTMaster.c
    glcdfont.c
    UserInterface.c
    main.c
    Display_FSM.c
    timer.c
)

target_link_libraries(final PRIVATE
    pico_stdlib
    pico_rand
    hardware_adc
    hardware_gpio
    hardware_pio
    hardware_irq
    pico_bootsel_via_double_reset
)

pico_add_extra_outputs(final)