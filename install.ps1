$Folder = '.\build'

if (Test-Path -Path $Folder) {
    Remove-Item -Path $Folder -Recurse -Force
    New-Item -Path $Folder -ItemType Directory
} else {
    New-Item -Path $Folder -ItemType Directory
}

cd $Folder
conan install .. --build=missing
cmake -G "Visual Studio 16 2019" ..
cmake --build .
