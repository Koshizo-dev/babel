let
  nixpkgs = import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/1e21c5807c4010c84c4628aab2af38a45c46c575.tar.gz") {};
  
in
with nixpkgs;

mkShell rec {

  nativeBuildInputs = [
    pkgconfig
    clang
    cmake
    lld # To use lld linker
  ];

  NIX_LD_LIBRARY_PATH = lib.makeLibraryPath [
    stdenv.cc.cc
  ];

#  QT_PLUGIN_PATH = qt5.qtwayland;
  QT_QPA_PLATFORM_PLUGIN_PATH = "${qt5.qtbase}/lib/qt-5.15.8/plugins/";
  
  NIX_LD = lib.fileContents "${stdenv.cc}/nix-support/dynamic-linker";

  JACK_INCLUDE_DIR="${jack2}/include";
  JACK_LIBRARY="${jack2}/lib/libjack.so";

  buildInputs = [
    xorg.libxcb.dev
    qt5.qtwayland
    asio
    jack2
    icu.dev
    openssl
    udev systemd
    alsaLib
    stdenv.cc.cc.lib
    gcc
    xkeyboard_config
    libffi
    libuuid.dev
    xorg.xcbutil.dev
    xorg.xcbutilrenderutil.dev
    xorg.xcbutilkeysyms.dev
    xorg.xcbutilimage.dev
    xorg.xcbutilwm.dev
    xorg.libXxf86vm.dev
    xorg.libXvMC.dev
    xorg.libXv.dev
    xorg.libXtst.out
    xorg.libXScrnSaver.out xorg.libXres.dev xorg.libXpm.dev xorg.libxkbfile.dev xorg.libXinerama.dev xorg.libXdmcp.dev xorg.libXdamage.dev xorg.libXcomposite.dev xorg.libXaw.dev xorg.libSM.dev xorg.libICE.dev xorg.libfontenc xorg.libXcursor xorg.libXrandr xorg.libXi # To use x11 feature
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
    boost
  ];

  shellHook = ''
  '';

  LD_LIBRARY_PATH = lib.makeLibraryPath buildInputs;

  PKG_CONFIG_PATH = pkgconfig;

  RUST_BACKTRACE = 1;

  WINIT_UNIX_BACKEND = "wayland";
}
