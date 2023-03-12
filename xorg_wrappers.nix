{ pkgs ? import <nixpkgs> {} }:

with pkgs;

{
  xorg_wrappers = [
    xorg.xcbutil.dev
    xorg.xcbutilrenderutil.dev
    xorg.xcbutilkeysyms.dev
    xorg.xcbutilimage.dev
    xorg.xcbutilwm.dev
    xorg.libXxf86vm.dev
    xorg.libXvMC.dev
    xorg.libXv.dev
    xorg.libXtst.out
    xorg.xinput
    xorg.libXScrnSaver.out
    xorg.libXres.dev
    xorg.libXpm.dev
    xorg.libxkbfile.dev
    xorg.libXinerama.dev
    xorg.libXdmcp.dev
    xorg.libXdamage.dev
    xorg.libXcomposite.dev
    xorg.libXaw.dev
    xorg.libSM.dev
    xorg.libICE.dev
    xorg.libfontenc
    xorg.libXcursor.dev
    xorg.libXrandr.dev
    xorg.libXi # To use x11 feature
  ];
}
