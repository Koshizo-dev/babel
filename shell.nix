let
  nixpkgs = import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/1e21c5807c4010c84c4628aab2af38a45c46c575.tar.gz") { };
  xorg_wrappers = import ./xorg_wrappers.nix { pkgs = nixpkgs; };
in
with nixpkgs;

mkShell rec {

  stdenv = clangStdenv;

  NIX_LD_LIBRARY_PATH = lib.makeLibraryPath [
    stdenv.cc.cc
  ];

  NIX_LD = lib.fileContents "${stdenv.cc}/nix-support/dynamic-linker";

  JACK_INCLUDE_DIR = "${jack2}/include";
  JACK_LIBRARY = "${jack2}/lib/libjack.so";

  shellHook = ''
  '';

  LD_LIBRARY_PATH = builtins.concatStringsSep ":" (map (x: toString x + "/lib") packages);

  PKG_CONFIG_PATH = pkgconfig;

  WINIT_UNIX_BACKEND = "wayland";

  packages = [
    pkgconfig
    clang-tools
    clang
    cmake
    lld # To use lld linker

    xorg_wrappers.xorg_wrappers
    fontconfig
    qt5.qtwayland
    asio
    jack2
    icu.dev
    openssl
    udev
    systemd
    alsaLib
    #stdenv.cc.cc.lib
    xkeyboard_config
    libffi
    libuuid.dev
    libxkbcommon
    libGL
    (pkgs.conan.overrideAttrs (oldAttrs: {
      src = fetchFromGitHub {
        owner = "conan-io";
        repo = "conan";
        rev = "refs/tags/1.57.0";
        hash = "sha256-9ovlSXL99YwAZYPNBdYgGbvXP26sg5852kjSiMV3Uxc=";
      };
      version = "1.57.0";
    }))

    qt5.full
  ];

}
