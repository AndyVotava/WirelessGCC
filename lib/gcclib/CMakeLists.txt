add_library(gcclib gccontroller.cpp gcconsole.cpp GCreport.cpp)

target_link_libraries(gcclib 
      pico_stdlib
      hardware_pio
      pico_time
)

pico_generate_pio_header(gcclib ${CMAKE_CURRENT_LIST_DIR}/pio/joybus.pio)
