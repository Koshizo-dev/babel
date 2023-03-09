# Add conan remote
`conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan`

# Linux build steps:

- `mkdir build && cd build`
- `conan install ..`
- `cmake ..`
- `make`
