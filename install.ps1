$Folder = '.\build'

if (Test-Path -Path $Folder) {
    Remove-Item -Path $Folder -Recurse -Force
    New-Item -Path $Folder -ItemType Directory
}
else {
    New-Item -Path $Folder -ItemType Directory
}

Set-Location $Folder
conan install .. --build=missing --profile mingw64
cmake -G "Visual Studio 17 2022" .. 
cmake --build . --target ALL_BUILD --config Release
Set-Location ..