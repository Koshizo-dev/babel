![Client preview](assets/preview.png)

# Update the conan settings
- `conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan`
- `conan config set general.revisions_enabled=1`

# Linux build steps:

- `mkdir build && cd build`
- `conan install .. --build missing`
- `cmake ..`
- `make`
