# Automatically generated by scripts/boost/generate-ports.ps1

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/units
    REF boost-1.83.0
    SHA512 f915fb2b77b98c0482a5d706dc51fc5f8887ce00848a58907f06cb740792221c21bd1785b5cc1c0e5e9a3c7c78bcf5c0528adbdb9b58db01bed5c3cdd4434b4b
    HEAD_REF master
)

include(${CURRENT_INSTALLED_DIR}/share/boost-vcpkg-helpers/boost-modular-headers.cmake)
boost_modular_headers(SOURCE_PATH ${SOURCE_PATH})
