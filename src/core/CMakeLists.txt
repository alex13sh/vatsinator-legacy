find_package (Qt5 5.7 REQUIRED COMPONENTS Core Network)

set (core_SOURCES
    airline.cpp
    airlinelistreader.cpp
    airport.cpp
    airportlistreader.cpp
    airportobject.cpp
    aliaslistreader.cpp
    atc.cpp
    atctracker.cpp
    client.cpp
    clientdata.cpp
    clientlist.cpp
    filedownloader.cpp
    filereader.cpp
    fir.cpp
    firlistreader.cpp
    firobject.cpp
    flightplan.cpp
    flighttracker.cpp
    geo.cpp
    lonlat.cpp
    metar.cpp
    metarmanager.cpp
    natparser.cpp
    option.cpp
    pilot.cpp
    pluginfinder.cpp
    resourcefile.cpp
    servertracker.cpp
    tmalistreader.cpp
    uirlistreader.cpp
    vatsimdatadocument.cpp
    vatsimdatareader.cpp
    vatsimstatusdocument.cpp
    vatsimstatusreader.cpp
)

set (core_HEADERS
    airline.h
    airlinelistreader.h
    airport.h
    airportlistreader.h
    airportobject.h
    aliaslistreader.h
    atc.h
    atctracker.h
    client.h
    clientdata.h
    clientlist.h
    filedownloader.h
    filereader.h
    fir.h
    firlistreader.h
    firobject.h
    flightplan.h
    flighttracker.h
    geo.h
    lonlat.h
    metar.h
    metarmanager.h
    natparser.h
    option.h
    pilot.h
    pluginfinder.h
    resourcefile.h
    servertracker.h
    tmalistreader.h
    uirlistreader.h
    vatsimdatadocument.h
    vatsimdatareader.h
    vatsimstatusdocument.h
    vatsimstatusreader.h
    
    core.h
)

set (core_PRIVATE_HEADERS

)

add_library (vtrcore SHARED ${core_SOURCES} ${core_HEADERS} ${core_PRIVATE_HEADERS})
target_link_libraries (vtrcore Qt5::Core Qt5::Network)
set_target_properties (vtrcore PROPERTIES CXX_VISIBILITY_PRESET hidden)

include (GenerateExportHeader)
generate_export_header(vtrcore)

install (TARGETS vtrcore
    EXPORT vtrcore
    RUNTIME DESTINATION ${vatsinator_BINARY_TARGET_DIR}
    LIBRARY DESTINATION ${vatsinator_LIBRARY_TARGET_DIR}
    ARCHIVE DESTINATION ${vatsinator_ARCHIVE_TARGET_DIR} CONFIGURATIONS Debug
)

add_subdirectory (resources)
