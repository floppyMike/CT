add_executable(AmpelSim main.cpp)

target_include_directories(AmpelSim PRIVATE ../include)

if(UNIX AND NOT APPLE)
        target_link_libraries(AmpelSim pthread)
elseif(WIN32)
        target_link_libraries(SPSCom libnodave)
endif()