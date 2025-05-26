cmake_minimum_required(VERSION 3.16)
project(InterfaceEleve LANGUAGES CXX)

# C++17 et activation automatique de moc/uic/rcc
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Modules Qt6 dont on a besoin
find_package(Qt6 REQUIRED COMPONENTS
  Core
  Widgets
  Multimedia
  Network
  Sql
)

# Sources, headers, .ui et .qrc
set(SOURCES
  main.cpp
  interfaceenregistrement.cpp
  audioCommunicator.cpp
  # ... ajoutez ici tous vos .cpp
)

set(HEADERS
  interfaceenregistrement.h
  audioCommunicator.h
  # ... vos .h
)

set(UIS
  interfaceenregistrement.ui
  # ... vos .ui
)

set(RCCS
  images.qrc
  # ... vos .qrc
)

# Déclaration de l’exécutable Qt
qt6_add_executable(InterfaceEleve
  ${SOURCES}
  ${HEADERS}
  ${UIS}
  ${RCCS}
)

# Linker avec les modules Qt
target_link_libraries(InterfaceEleve PRIVATE
  Qt6::Core
  Qt6::Widgets
  Qt6::Multimedia
  Qt6::Network
  Qt6::Sql
)
