set(COMPONENT_SRCS "radio.c")
set(COMPONENT_ADD_INCLUDEDIRS include)
set(COMPONENT_REQUIRES audio_stream audio_pipeline esp_peripherals)
register_component()